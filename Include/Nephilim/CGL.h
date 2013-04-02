#ifndef CGL_h__
#define CGL_h__

#include "Platform.h"

void cglPrepareExtensions();

/// All desktop platforms
#if defined NEPHILIM_DESKTOP
#include <GL/glew.h>
#include <GL/gl.h>

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
#if defined NEPHILIM_ANDROID
#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>

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
#if defined NEPHILIM_IOS
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#endif

#endif // CGL_h__
