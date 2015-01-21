#include <Nephilim/Platform.h>
#include <Nephilim/Logger.h>

#ifdef NEPHILIM_ANDROID

#include <Nephilim/Foundation/AndroidWrapper.h>
#include <Nephilim/Foundation/File.h>

#include <assert.h>

NEPHILIM_NS_BEGIN
	 

String AndroidWrapper::m_AssetSuffix = ".png";
String AndroidWrapper::m_packageName = "unknown";
String AndroidWrapper::m_JNIActivityName = "unknown";
JavaVM* AndroidWrapper::m_javaVM = NULL;
String AndroidWrapper::m_externalStorageDirectory = "";
String AndroidWrapper::m_internalDataPath = "";


/// Sets the internal data path
void AndroidWrapper::setInternalDataPath(const String& path)
{
	m_internalDataPath = path;
}

/// Get the internal data path of the application, where the save files are stored
String AndroidWrapper::getInternalDataPath()
{
	return m_internalDataPath;
}

/// Set the asset suffix to be automatically applied to paths
void AndroidWrapper::setAssetSuffix(const String &suffix){
	m_AssetSuffix = suffix;
};

/// Get the current asset suffix
String AndroidWrapper::getAssetSuffix(){
	return m_AssetSuffix;
};

bool AndroidWrapper::getAssetFile(File* file, const String &path, bool binaryMode){
	if(path.empty() || file == NULL)return false; // No path

	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);

	String realPath = path;

	bool isAPKAsset = (path[0] != '/');
	if(isAPKAsset){
		realPath += m_AssetSuffix;
		//String realPathh = realPath + "" + ".png";



		jclass afdclass = m_JNI->FindClass("android/content/res/AssetFileDescriptor");
		jclass activityclass = m_JNI->FindClass(m_JNIActivityName);
		if(afdclass != NULL && activityclass != NULL){
			jmethodID afdgetmethod = m_JNI->GetStaticMethodID(activityclass, "getAssetFileDescriptor", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
			if(afdgetmethod != NULL){
				jstring pathString = m_JNI->NewStringUTF(realPath.c_str()); //deallocate
				jobject afd = m_JNI->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
				m_JNI->DeleteLocalRef(pathString);
				if(afd != NULL){   
					/// Found the asset file descriptor, will be able build the FILE* now
					jclass fdclass = m_JNI->FindClass("java/io/FileDescriptor");
					if(fdclass){
						jmethodID getlenmethod = m_JNI->GetMethodID(afdclass, "getDeclaredLength", "()J");
						jlong len = m_JNI->CallLongMethod(afd, getlenmethod);
						long length = len;	

						jmethodID getoffsetmethod = m_JNI->GetMethodID(afdclass, "getStartOffset", "()J");
						jlong offset_ = m_JNI->CallLongMethod(afd, getoffsetmethod);
						long offset = offset_;
			
						jclass afdclass2 = m_JNI->GetObjectClass(afd);
						jmethodID getfdmethod = m_JNI->GetMethodID(afdclass, "getFileDescriptor", "()Ljava/io/FileDescriptor;");
						jobject fd = m_JNI->CallObjectMethod(afd, getfdmethod);
						if(fd){
							/// I have a file descriptor . convert to a FILE*
							jclass refc = (jclass)m_JNI->NewGlobalRef(fdclass);
							jfieldID field = m_JNI->GetFieldID(refc, "descriptor", "I"); 
							jint fdnn = m_JNI->GetIntField(fd,field);

							int realFd = dup(fdnn);
							FILE* fpointer;
							if(binaryMode){
								fpointer = fdopen(realFd, "rb");
							}
							else {
								fpointer = fdopen(realFd, "r");
							} 
							if(fpointer != NULL){
								file->open(fpointer , offset, length);
							}
							else
								return false;
						}
					}
				} 
				else{
					return false; // APK RESOURCE NOT FOUND
				}
			}
		}

	} // if(isAPKAsset)
	else{
		// It is not an APK resource, do normal loading
		FILE* fpointer = NULL;

		if(binaryMode){
			fpointer = fopen(realPath.c_str(), "rb");
		}
		else{
			fpointer = fopen(realPath.c_str(), "r");
		}
		
		if(fpointer == NULL) return false;
			
		// assign
		file->open(fpointer, 0, -1); // Open the file as a whole

//		TESTLOG("Opened file regularly.")
		//TESTLOG(realPath.c_str())
	}	

	return true;
}

AndroidWrapper::AssetFile AndroidWrapper::getAsset(const String& filename)
{
	AssetFile result;
	result.success = false;

	assert(m_javaVM != NULL);

	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);

	String realPath = filename + ".png";

	jclass afdclass = m_JNI->FindClass("android/content/res/AssetFileDescriptor");
	jclass activityclass = m_JNI->FindClass(m_JNIActivityName);
	if(afdclass != NULL && activityclass != NULL){
		jmethodID afdgetmethod = m_JNI->GetStaticMethodID(activityclass, "getAssetFileDescriptor", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
		if(afdgetmethod != NULL){
			jstring pathString = m_JNI->NewStringUTF(realPath.c_str()); //deallocate
			jobject afd = m_JNI->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
			m_JNI->DeleteLocalRef(pathString);
			if(afd != NULL){   
				/// Found the asset file descriptor, will be able build the FILE* now
				jclass fdclass = m_JNI->FindClass("java/io/FileDescriptor");
				if(fdclass){
					jmethodID getlenmethod = m_JNI->GetMethodID(afdclass, "getDeclaredLength", "()J");
					jlong len = m_JNI->CallLongMethod(afd, getlenmethod);
					long length = len;	

					jmethodID getoffsetmethod = m_JNI->GetMethodID(afdclass, "getStartOffset", "()J");
					jlong offset_ = m_JNI->CallLongMethod(afd, getoffsetmethod);
					long offset = offset_;

					jclass afdclass2 = m_JNI->GetObjectClass(afd);
					jmethodID getfdmethod = m_JNI->GetMethodID(afdclass, "getFileDescriptor", "()Ljava/io/FileDescriptor;");
					jobject fd = m_JNI->CallObjectMethod(afd, getfdmethod);
					if(fd){
						/// I have a file descriptor
						jclass refc = (jclass)m_JNI->NewGlobalRef(fdclass);
						jfieldID field = m_JNI->GetFieldID(refc, "descriptor", "I"); 
						jint fdnn = m_JNI->GetIntField(fd,field);

						int realFd = dup(fdnn);

						result.success = true;
						result.fd = realFd;
						result.offset = offset;
						result.length = length;
					}
				}
			} 
		}
	}

	return result;
}

/// Get a listing of files/directories within the APK assets, empty path will mean the root directory of assets
StringList AndroidWrapper::getAssetList(const String &path){
	StringList files;
	
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass activityclass = m_JNI->FindClass(m_JNIActivityName);
	if(activityclass != NULL){
		jmethodID afdgetmethod = m_JNI->GetStaticMethodID(activityclass, "getAssetList", "(Ljava/lang/String;)[Ljava/lang/String;");
		if(afdgetmethod != NULL){
			jstring pathString = m_JNI->NewStringUTF(path.c_str());
			jobject afd = m_JNI->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
			m_JNI->DeleteLocalRef(pathString);
			if(afd != NULL){
				//find size of the array
				jobjectArray arr = (jobjectArray)afd;
				if(arr){
					//i have the array
					for(int i = 0; i < m_JNI->GetArrayLength((jarray)arr); i++){
						jstring fileString = (jstring)m_JNI->GetObjectArrayElement(arr, i);
						String finalFile = path + "/" + m_JNI->GetStringUTFChars(fileString, NULL);
						finalFile.erase(finalFile.end() - m_AssetSuffix.size(), finalFile.end());
						files.append(finalFile);
						m_JNI->DeleteLocalRef(fileString);
					}					 
				}			
			}
		}
	}
	
	return files;
};

/// Attempts to create a directory in the Android file system
/// Make sure you have the needed permissions in the manifest
bool AndroidWrapper::createDirectory(const String& path)
{
	bool result = false;

	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass activityclass = m_JNI->FindClass(m_JNIActivityName);
	if(activityclass != NULL){
		jmethodID afdgetmethod = m_JNI->GetStaticMethodID(activityclass, "createDirectory", "(Ljava/lang/String;)Z");
		if(afdgetmethod != NULL){
			jstring pathString = m_JNI->NewStringUTF(path.c_str());
			jobject boole = m_JNI->CallStaticObjectMethod(activityclass, afdgetmethod, pathString);
			if(boole)
			{
				result = (bool)(boole != JNI_FALSE);
			}
			m_JNI->DeleteLocalRef(pathString);			
			
		}
	}

	return result;
};

/// Sends a text message through the android device, please note the permissions must be requested in the manifest and the legacy java source must be in place.
bool AndroidWrapper::sendTextMessage(const String &destinationNumber, const String &content){
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){
		jmethodID method = m_JNI->GetStaticMethodID(cls, "sendSMS", "(Ljava/lang/String;Ljava/lang/String;)V");
		if(method != NULL){
			jstring num = m_JNI->NewStringUTF(destinationNumber.c_str());
			jstring con = m_JNI->NewStringUTF(content.c_str());

			m_JNI->CallStaticVoidMethod(cls, method, num, con);
			
			m_JNI->DeleteLocalRef(num);
			m_JNI->DeleteLocalRef(con);
			
			return true; // sucessfull send
		}
		else return false;
	}
	else return false;
};

/// Closes the activity, ending the application
void AndroidWrapper::closeActivity(){
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){
		jmethodID method = m_JNI->GetStaticMethodID(cls, "closeActivity", "()V");
		if(method != NULL){			
			m_JNI->CallStaticVoidMethod(cls, method);	
		}
	}
};

/// Request a frame render
void AndroidWrapper::requestFrameRender()
{
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "requestFrameRender", "()V");
		if(method != NULL){
			m_JNI->CallStaticVoidMethod(cls, method);
		}
	}  
};

/// Enable multitouch support
void AndroidWrapper::enableMultiTouch()
{
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "enableMultiTouch", "()V");
		if(method != NULL){
			m_JNI->CallStaticVoidMethod(cls, method);
		}
	}
}

/// Disable multitouch support
void AndroidWrapper::disableMultiTouch()
{
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "disableMultiTouch", "()V");
		if(method != NULL){
			m_JNI->CallStaticVoidMethod(cls, method);
		}
	}  
}

/// Toggle the software keyboard
void AndroidWrapper::toggleKeyboard(){
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "toggle_keyboard", "()V");
		if(method != NULL){
			m_JNI->CallStaticVoidMethod(cls, method);
		}
	} 
};

/// Play a music in the android
int AndroidWrapper::playMusic(const String &name){
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "playMusic", "(Ljava/lang/String;)V");
		if(method != NULL){
			jstring fpath = m_JNI->NewStringUTF(String(name + ".png").c_str());
			m_JNI->CallStaticVoidMethod(cls, method, fpath);
			m_JNI->DeleteLocalRef(fpath);
		}
	}
	return 0;
};

/// Set the directory of the external storage, the sdcard in case of the android
void AndroidWrapper::setExternalStorageDirectory(const String& path){
	m_externalStorageDirectory = path;
};

/// Get the external storage directory, the path to the sdcard root
String AndroidWrapper::getExternalStorageDirectory(){
	return m_externalStorageDirectory;
};
 
/// Set the JNI environment the application is using
void AndroidWrapper::setJavaNativeInterfaceEnvironment(JavaVM *environment){
	m_javaVM = environment;
};

/// Get the android package name
String AndroidWrapper::getPackageName(){
	return m_packageName;
};

/// Set the android package name
void AndroidWrapper::setPackageName(const String &name){
	m_packageName = name;
};

/// Get the android activity name
String AndroidWrapper::getActivityName(){
	return m_JNIActivityName;
};

/// Set the android activity name
void AndroidWrapper::setActivityName(const String& name){
	m_JNIActivityName = name;
	for(unsigned int i = 0; i < m_JNIActivityName.length(); i++){
		// replace all . with / for the jni
		if(m_JNIActivityName[i] == '.') m_JNIActivityName[i] = '/';
	}
};

/// Vibrate the device for miliseconds
void AndroidWrapper::vibrate(int miliseconds)
{
	JNIEnv* m_JNI;
	m_javaVM->AttachCurrentThread(&m_JNI, NULL);	

	jclass cls = m_JNI->FindClass(m_JNIActivityName);
	if(cls != NULL){ 
		jmethodID method = m_JNI->GetStaticMethodID(cls, "vibrate", "(J)V");
		if(method != NULL){
			jlong val = miliseconds;
			m_JNI->CallStaticVoidMethod(cls, method, val);
			   
		}
	}
};



NEPHILIM_NS_END

#endif // NO COMPILATION FOR NON-ANDROID PLATFORMS