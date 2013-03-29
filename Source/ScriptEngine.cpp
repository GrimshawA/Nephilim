#ifndef MINIMAL_BUILD

#include "Nephilim/ScriptEngine.h"
#include "Nephilim/GameCore.h"
#include "Nephilim/ScriptEngineDefault.h"
#include "Nephilim/StringList.h"
#include <iostream>

NEPHILIM_NS_BEGIN



/// Creates an empty script engine and registers the default ones immediately
ScriptEngine::ScriptEngine(){
	registerDefaultCommands();
};

/// Safely destroys itself and its child tasks
ScriptEngine::~ScriptEngine(){
	for(std::map<String, ScriptEngineTask*>::iterator it = myCommands.begin(); it != myCommands.end(); it++){
		it->second->removeReference();
	}
};

/// Run a command
void ScriptEngine::run(const String &command){
	if(command.empty())return;

	String command2 = command;

	StringList cmd = command2.split(" ", 1);

	if(cmd.empty())return;

	cmd[0].toLowerCase();

	std::map<String, ScriptEngineTask*>::iterator it = myCommands.find(cmd[0]);
	if(it != myCommands.end()){
		//std::cout<<"executing: "<<command<<std::endl;
		if(cmd.size() < 2){
			cmd.append("");
		}
		if(it->second->enabled)
			it->second->run(cmd[0], cmd[1]);
		else
			std::cout<<">> Hidden task: "<<cmd[0]<<std::endl;
	}
	else{
		std::cout<<">> Invalid task: "<<cmd[0]<<std::endl;
	}	
};

/// Registers a task instance as an available command, responding by
/// the name specified, case-insensitive
void ScriptEngine::registerTask(String &name, ScriptEngineTask* task){
	myCommands[name] = task;
	task->refCount ++;
	task->myParent = this;
};

void ScriptEngine::registerDefaultCommands(){
	registerTask(String("echo"), new EchoTask());
	registerTask(String("gethttp"), new GetHttpTask());
	registerTask(String("parse"), new ParseTask());
}

/// Hides all the default tasks at once, that means they cannot be executed anymore
void ScriptEngine::hideDefaultTasks(){
	hideTask(String("echo"));
	hideTask(String("gethttp"));
	hideTask(String("parse"));
};

/// Shows all the default tasks at once, that means you can call them again
void ScriptEngine::showDefaultTasks(){
	showTask(String("echo"));
	showTask(String("gethttp"));
	showTask(String("parse"));
};

/// Hide a task from execution
void ScriptEngine::hideTask(const String &task_name){
	std::map<String, ScriptEngineTask*>::iterator it = myCommands.find(task_name);
	if(it != myCommands.end()){
		//found, hide
		it->second->enabled = false;
	}
};

/// Enables a task for execution back again
void ScriptEngine::showTask(const String &task_name){
	std::map<String, ScriptEngineTask*>::iterator it = myCommands.find(task_name);
	if(it != myCommands.end()){
		//found, hide
		it->second->enabled = true;
	}
};

NEPHILIM_NS_END
#endif