#ifndef CGL_h__
#define CGL_h__

#include "Platform.h"

void cglPrepareExtensions();

/// All desktop platforms
#if defined NEPHILIM_DESKTOP
#include <GL/glew.h>

#ifdef NEPHILIM_OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// FBO
#define glGenFramebuffersCGL glGenFramebuffersEXT
#define glFramebufferTexture2DCGL glFramebufferTexture2DEXT
#define glCheckFramebufferStatusCGL glCheckFramebufferStatusEXT
#define glBindFramebufferCGL glBindFramebufferEXT
#define GL_FRAMEBUFFER_CGL GL_FRAMEBUFFER_EXT
#define GL_COLOR_ATTACHMENT0_CGL GL_COLOR_ATTACHMENT0_EXT
#define GL_DEPTH_ATTACHMENT_CGL GL_DEPTH_ATTACHMENT_EXT
#define GL_FRAMEBUFFER_COMPLETE_CGL GL_FRAMEBUFFER_COMPLETE_EXT

#endif

/// Android GLES 1.1
#if defined NEPHILIM_ANDROID
//#define GL_GLEXT_PROTOTYPES
///#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// FBO
#define glGenFramebuffersCGL glGenFramebuffers
#define glFramebufferTexture2DCGL glFramebufferTexture2D
#define glCheckFramebufferStatusCGL glCheckFramebufferStatus
#define glBindFramebufferCGL glBindFramebuffer
#define GL_FRAMEBUFFER_CGL GL_FRAMEBUFFER
#define GL_COLOR_ATTACHMENT0_CGL GL_COLOR_ATTACHMENT0
#define GL_FRAMEBUFFER_COMPLETE_CGL GL_FRAMEBUFFER_COMPLETE

#endif

/// Include iPhone GLES Headers
#if defined NEPHILIM_IOS
#warning IOS detected
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#endif

#endif // CGL_h__
