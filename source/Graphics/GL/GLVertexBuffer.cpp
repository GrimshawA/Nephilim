#include <Nephilim/Graphics/GL/GLVertexBuffer.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>
#include <Nephilim/Graphics/VertexArray.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

namespace
{
	GLenum getGLUsageMode(GLVertexBuffer::StorageMode mode)
	{
		GLenum usageMode;
		switch (mode)
		{
		case GLVertexBuffer::StaticDraw: usageMode = GL_STATIC_DRAW; break;
		case GLVertexBuffer::DynamicDraw: usageMode = GL_DYNAMIC_DRAW; break;
		case GLVertexBuffer::StreamDraw: usageMode = GL_STREAM_DRAW; break;

#ifdef NEPHILIM_DESKTOP
		case GLVertexBuffer::StreamCopy: usageMode = GL_STREAM_COPY; break;
		case GLVertexBuffer::StreamRead: usageMode = GL_STREAM_READ; break;
		case GLVertexBuffer::DynamicCopy: usageMode = GL_DYNAMIC_COPY; break;
		case GLVertexBuffer::DynamicRead: usageMode = GL_DYNAMIC_READ; break;
		case GLVertexBuffer::StaticCopy: usageMode = GL_STATIC_COPY; break;
		case GLVertexBuffer::StaticRead: usageMode = GL_STATIC_READ; break;
#endif
		default: usageMode = GL_STATIC_DRAW; break;
		}
		return usageMode;
	}
}

/// Initializes the vertex buffer to an invalid state
GLVertexBuffer::GLVertexBuffer()
: mObject(0)
{
}

/// Make sure the opengl resource has been released and its data
GLVertexBuffer::~GLVertexBuffer()
{
	destroy();
}

/// Initializes the vertex buffer to a valid state
void GLVertexBuffer::create()
{
	// Don't initialize unless there is nothing previously allocated
	if (mObject == 0)
	{
		glGenBuffers(1, &mObject);
	}
}


/// Eliminate the opengl resource and its data
void GLVertexBuffer::destroy()
{
	if (mObject)
	{
		glDeleteBuffers(1, &mObject);
		mObject = 0;
	}
}

void GLVertexBuffer::bind()
{
	if (mObject)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mObject);
	}
}

/// Check if the VBO is valid (initialized)
GLVertexBuffer::operator bool() const
{
	return (mObject > 0);
}

/// Upload a VertexArray to the GPU memory
void GLVertexBuffer::upload(const VertexArray& vertexArray, StorageMode mode)
{
	if (mObject)
	{
		GLenum usageMode = getGLUsageMode(mode);

		glBufferData(GL_ARRAY_BUFFER, vertexArray.getMemorySize(), &vertexArray._data[0], usageMode);
	}
}

/// Initializes GPU memory with <size> bytes and the desired access mode
void GLVertexBuffer::resize(Int32 size, StorageMode mode)
{
	if (mObject)
	{
		GLenum usageMode = getGLUsageMode(mode);

		glBufferData(GL_ARRAY_BUFFER, size, NULL, usageMode);
	}
}


NEPHILIM_NS_END
