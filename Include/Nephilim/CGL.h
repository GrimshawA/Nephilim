#ifndef CGL_h__
#define CGL_h__

#include "Platform.h"

/// Utility
void cglPrepareExtensions();

/// All desktop platforms
#if defined PARABOLA_DESKTOP
#include <GL/glew.h>
#include <GL/GL.h>

static void cglPrepareExtensions()
{
	glewInit();
}
// FBO
#define glGenFramebuffersCGL glGenFramebuffersEXT
#define glFramebufferTexture2DCGL glFramebufferTexture2DEXT
#define glCheckFramebufferStatusCGL glCheckFramebufferStatusEXT
#define glBindFramebufferCGL glBindFramebufferEXT
#define GL_FRAMEBUFFER_CGL GL_FRAMEBUFFER_EXT
#define GL_COLOR_ATTACHMENT0_CGL GL_COLOR_ATTACHMENT0_EXT
#define GL_FRAMEBUFFER_COMPLETE_CGL GL_FRAMEBUFFER_COMPLETE_EXT

#endif

/// Android GLES 1.1
#if defined PARABOLA_ANDROID
#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>

void cglPrepareExtensions(){}
// FBO
#define glGenFramebuffersCGL glGenFramebuffersOES
#define glFramebufferTexture2DCGL glFramebufferTexture2DOES
#define glCheckFramebufferStatusCGL glCheckFramebufferStatusOES
#define glBindFramebufferCGL glBindFramebufferOES
#define GL_FRAMEBUFFER_CGL GL_FRAMEBUFFER_OES
#define GL_COLOR_ATTACHMENT0_CGL GL_COLOR_ATTACHMENT0_OES
#define GL_FRAMEBUFFER_COMPLETE_CGL GL_FRAMEBUFFER_COMPLETE_OES

#endif

/// Include iPhone GLES Headers
#if defined PARABOLA_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#endif

#endif // CGL_h__
