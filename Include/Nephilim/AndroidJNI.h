#ifndef PARABOLA_ANDROIDJNI
#define PARABOLA_ANDROIDJNI

extern void android_init();
extern void android_gl_reload();
extern void android_render();
extern void android_resize(int w, int h);
extern void android_touchdown(float x, float y);
extern void android_touchup(float x, float y);
extern void android_touchmove(float x, float y);
extern void android_keydown(int key);
 
#include "ParabolaCore/Strings.h"
#include "ParabolaCore/AndroidInterface.h"
 
// JNI Header
#include <jni.h>

#include <android/log.h>

#include <android/keycodes.h>

JNIEnv* jEnv = NULL;

#define PASTER(x,y,z) Java_ ## y ## _ ## z ## _ ## x
#define EVALUATOR(x,y,z)  PASTER(x,y,z)
#define JNI_ACTIVITY_FUNC(fun) EVALUATOR(fun, ANDROID_PACKAGE_NAME, ANDROID_ACTIVITY_NAME)

#define PASTER2(x,y) Java_ ## y ## _ ## x
#define EVALUATOR2(x,y)  PASTER2(x,y)
#define JNI_PACKAGE_FUNC(fun) EVALUATOR2(fun, ANDROID_PACKAGE_NAME)

extern "C"{   
	JNIEXPORT void
		JNI_ACTIVITY_FUNC(nativeStorageInfo) ( JNIEnv*  env , jobject thiz, jstring internalDataPath, jstring externalDataPath, jboolean externalDataWriteable, jboolean externalDataAvailable, jstring packageName, jstring activityName);
	JNIEXPORT void
		JNI_ACTIVITY_FUNC(nativeKeyDown) ( JNIEnv*  env , jobject thiz, jint keyCode);
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoRenderer_nativeInit) ( JNIEnv*  env );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoRenderer_nativeSurfaceCreated) ( JNIEnv*  env );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoRenderer_nativeRender) ( JNIEnv*  env );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoRenderer_nativeResize) ( JNIEnv*  env, jobject thiz, jint w, jint h );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchDown) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchUp) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y );
	JNIEXPORT void
		JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchMove) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y );
	JNIEXPORT jint
		JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeGetGLVersion) ( JNIEnv*  env, jobject thiz );

	JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *reserved);
};

JNIEXPORT jint JNI_OnLoad(JavaVM *jvm, void *reserved){
	__android_log_print(ANDROID_LOG_INFO, "TestingFacilities", "ONLOAD CALLED\n");
	pE::AndroidInterface::setJavaNativeInterfaceEnvironment(jvm);
	return JNI_VERSION_1_2;
};

JNIEXPORT void
	JNI_ACTIVITY_FUNC(nativeStorageInfo) ( JNIEnv*  env , jobject thiz, jstring internalDataPath, jstring externalDataPath, jboolean externalDataWriteable, jboolean externalDataAvailable, jstring packageName, jstring activityName){
		pE::String s1, s2, s3, s4; 
		s1 = env->GetStringUTFChars(internalDataPath, 0);
		s2 = env->GetStringUTFChars(externalDataPath, 0);
		s3 = env->GetStringUTFChars(packageName, 0);
		s4 = env->GetStringUTFChars(activityName, 0);

		
		pE::AndroidInterface::setPackageName(s3);
		pE::AndroidInterface::setActivityName(s4);
		pE::AndroidInterface::setExternalStorageDirectory(s2);

		myApp.myDataDirectory = s1;
		myApp.myExternalStorageDirectory = s2; 

		__android_log_print(ANDROID_LOG_INFO, "TestingFacilities", "Paths: %s\n%s", s1.c_str(), s2.c_str());
		__android_log_print(ANDROID_LOG_INFO, "TestingFacilities", "Package: %s\n", s3.c_str());
		__android_log_print(ANDROID_LOG_INFO, "TestingFacilities", "Activity: %s\n", s4.c_str());
}

 
JNIEXPORT void	JNI_ACTIVITY_FUNC(nativeKeyDown) ( JNIEnv*  env , jobject thiz, jint keyCode){
	android_keydown(keyCode);
} 

JNIEXPORT void JNI_PACKAGE_FUNC(DemoRenderer_nativeInit)( JNIEnv*  env ){
	jEnv = env;	 
	//pE::AndroidInterface::setJavaNativeInterfaceEnvironment(env);
	android_init();  
};

/// Used to detect GL context lost
static bool surfaceCreatedAtLeastOnce = false;
JNIEXPORT void JNI_PACKAGE_FUNC(DemoRenderer_nativeSurfaceCreated)( JNIEnv*  env ){

	if(!surfaceCreatedAtLeastOnce)
	{
		surfaceCreatedAtLeastOnce = true; 
	}
	else
	{
		android_gl_reload();
	}
};

JNIEXPORT void JNI_PACKAGE_FUNC(DemoRenderer_nativeRender) ( JNIEnv*  env ){
	android_render();
}

JNIEXPORT void JNI_PACKAGE_FUNC(DemoRenderer_nativeResize) ( JNIEnv*  env, jobject thiz, jint w, jint h ){
	android_resize(w,h);
}; 

JNIEXPORT void JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchDown) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y ){
	android_touchdown(x,y);	
};
JNIEXPORT void JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchUp) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y ){
	android_touchup(x,y);
};
JNIEXPORT void JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeTouchMove) ( JNIEnv*  env, jobject thiz, jfloat x, jfloat y ){
	android_touchmove(x,y);   
};

JNIEXPORT jint JNI_PACKAGE_FUNC(DemoGLSurfaceView_nativeGetGLVersion) ( JNIEnv*  env, jobject thiz )
{
	__android_log_print(ANDROID_LOG_INFO, "Engine", "Attempting to create a OpenGL ES 2.0 context.\n");
#if defined PARABOLA_PREFER_GLES2
	return 2;
#else
	return 1;
#endif
};

#endif