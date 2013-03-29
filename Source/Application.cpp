#include <Nephilim/Application.h>
#include <Nephilim/Logger.h>
#include <Nephilim/ScopedFile.h>


NEPHILIM_NS_BEGIN

/// Shuts down the environment for program closure
void Application::close(){
#ifdef PARABOLA_ANDROID
	AndroidInterface::closeActivity();
#endif
}






std::vector<Event> Application::pendingEvents;

Application* Application::myInstance = NULL;

Application::Application(){
	myInstance = this;
	m_running = true;

#ifdef PARABOLA_DESKTOP
	myPlatformType = ApplicationSettings::Desktop;
#elif defined PARABOLA_ANDROID || defined PARABOLA_IPHONE
	myPlatformType = ApplicationSettings::Mobile;	
#endif
}

int Application::getPlatformType(){
	return myInstance->myPlatformType;
}

/// True while the application is alive
bool Application::running(){
	return m_running;
};


ScopedFile* Application::getAssetFile(String &path){
	/*
#ifdef PARABOLA_ANDROID	 
	 
	path += ".png"; //for now

	jclass afdclass = jniEnv->FindClass("android/content/res/AssetFileDescriptor");
	jclass activityclass = jniEnv->FindClass("com/parabolaengine/crossgame/CrossGame");
	if(afdclass != NULL && activityclass != NULL){
		jmethodID afdgetmethod = jniEnv->GetStaticMethodID(activityclass, "getAssetFileDescriptor", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
		if(afdgetmethod != NULL){
			jstring pathString = jniEnv->NewStringUTF(path.c_str());
			jobject afd = jniEnv->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
			if(afd != NULL){   
				//TESTLOG("FOUND ASSSET!!!!!!\n")

				// now convert to FILE*

				jclass fdclass = jniEnv->FindClass("java/io/FileDescriptor");
				if(fdclass){
					jmethodID getlenmethod = jniEnv->GetMethodID(afdclass, "getDeclaredLength", "()J");
					jlong len = jniEnv->CallLongMethod(afd, getlenmethod);
					long length = len;

					jmethodID getoffsetmethod = jniEnv->GetMethodID(afdclass, "getStartOffset", "()J");
					jlong offset_ = jniEnv->CallLongMethod(afd, getoffsetmethod);
					long offset = offset_;

					jclass afdclass2 = jniEnv->GetObjectClass(afd);
					jmethodID getfdmethod = jniEnv->GetMethodID(afdclass, "getFileDescriptor", "()Ljava/io/FileDescriptor;");
					jobject fd = jniEnv->CallObjectMethod(afd, getfdmethod);
					if(fd){
						//TESTLOG("Got fd\n\n")

						jclass refc = (jclass)jniEnv->NewGlobalRef(fdclass);
						jfieldID field = jniEnv->GetFieldID(refc, "descriptor", "I"); 
						jint fdnn = jniEnv->GetIntField(fd,field);

						int realFd = dup(fdnn);

						FILE* realFile = fdopen(realFd, "rb");
						if(realFile != NULL){
							// Sucessfully found the wanted file.
							
							ScopedFile *stream = new ScopedFile(realFile, offset, length);
							return stream;
						}
						else return NULL;
					}
				}
			} 
			else{
				TESTLOG("NO ASSET...\n")
			}
		}
	}
	else{
		TESTLOG("Something went wrong with the classes in getAssetFile()\n")
	}

	
	//jclass fdClass = jniEnv->FindClass("java/io/FileDescriptor");	
///	jclass ref = (jclass)env->NewGlobalRef(fdClass);
	//jfieldID field = env->GetFieldID(ref, "descriptor", "I");
	//jint fd = env->GetIntField(fdobj,field);


#endif
	*/
	return NULL;
}

StringList Application::getAssetList(String path){
	StringList files;
	/*
#ifdef PARABOLA_ANDROID 
	jclass activityclass = jniEnv->FindClass("com/parabolaengine/crossgame/CrossGame");
	if(activityclass != NULL){
		jmethodID afdgetmethod = jniEnv->GetStaticMethodID(activityclass, "getAssetList", "(Ljava/lang/String;)[Ljava/lang/String;");
		if(afdgetmethod != NULL){
			jstring pathString = jniEnv->NewStringUTF(path.c_str());
			jobject afd = jniEnv->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
			if(afd != NULL){   
				TESTLOG("I HAVE THE ASSETS LISTING\n")

				//find size of the array
				jobjectArray arr = (jobjectArray)afd;
				if(arr){
					//i have the array
					for(int i = 0; i < jniEnv->GetArrayLength((jarray)arr); i++){
						jstring fileString = (jstring)jniEnv->GetObjectArrayElement(arr, i);
						String finalFile = path + "/" + jniEnv->GetStringUTFChars(fileString, NULL);
						finalFile.erase(finalFile.end()-4, finalFile.end());
						files.append(finalFile);
						
					}
					 
				}
				 
			
			}
		}
	}
#endif
	*/
	return files;
}


/*
void Application::MobileServices::sendTextMessage(String number, String content){
#ifdef PARABOLA_ANDROID
	jclass cls = jniEnv->FindClass("com/parabolaengine/crossgame/CrossGame");
	if(cls == NULL){
		TESTLOG("CLASS NOT FOUND\n")
	} 

	jmethodID method = jniEnv->GetStaticMethodID(cls, "sendSMS", "(Ljava/lang/String;Ljava/lang/String;)V");
	if(method != NULL){
		jstring num = jniEnv->NewStringUTF(number.c_str());
		jstring con = jniEnv->NewStringUTF(content.c_str());

		jniEnv->CallStaticVoidMethod(cls, method, num, con);
		TESTLOG("sms sent\n")
	}
	else{
		TESTLOG("Something failed in sending sms\n")
	}

	
#endif
};
*/
NEPHILIM_NS_END