#include <Nephilim/Graphics/VertexBuffer.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/CGL.h>


NEPHILIM_NS_BEGIN

namespace
{
	GLenum getGLUsageMode(VertexBuffer::StorageMode mode)
	{
		GLenum usageMode;
		switch(mode)
		{
		case VertexBuffer::StaticDraw: usageMode = GL_STATIC_DRAW; break;	
		case VertexBuffer::DynamicDraw: usageMode = GL_DYNAMIC_DRAW; break;		
		case VertexBuffer::StreamDraw: usageMode = GL_STREAM_DRAW; break;
		
#ifdef NEPHILIM_DESKTOP
		case VertexBuffer::StreamCopy: usageMode = GL_STREAM_COPY; break;
		case VertexBuffer::StreamRead: usageMode = GL_STREAM_READ; break;
		case VertexBuffer::DynamicCopy: usageMode = GL_DYNAMIC_COPY; break;
		case VertexBuffer::DynamicRead: usageMode = GL_DYNAMIC_READ; break;	
		case VertexBuffer::StaticCopy: usageMode = GL_STATIC_COPY; break;
		case VertexBuffer::StaticRead: usageMode = GL_STATIC_READ; break;
#endif
		default: usageMode = GL_STATIC_DRAW; break;
		}
		return usageMode;
	}
}

/// Initializes the vertex buffer to an invalid state
VertexBuffer::VertexBuffer()
: mObject(0)
{
}

/// Make sure the opengl resource has been released and its data
VertexBuffer::~VertexBuffer()
{
	destroy();
}

/// Initializes the vertex buffer to a valid state
void VertexBuffer::create()
{
	// Don't initialize unless there is nothing previously allocated
	if(mObject == 0)
	{
		glGenBuffers(1, &mObject);
	}
}


/// Eliminate the opengl resource and its data
void VertexBuffer::destroy()
{
	if(mObject)
	{
		glDeleteBuffers(1, &mObject);
		mObject = 0;
	}
}

void VertexBuffer::bind()
{
	if(mObject)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mObject);
	}
}

/// Check if the VBO is valid (initialized)
VertexBuffer::operator bool() const
{
	return (mObject > 0);
}

/// Upload a VertexArray to the GPU memory
void VertexBuffer::upload(const VertexArray& vertexArray, StorageMode mode)
{
	if(mObject)
	{
		GLenum usageMode = getGLUsageMode(mode);		

		glBufferData(GL_ARRAY_BUFFER, vertexArray.getMemorySize(), &vertexArray._data[0], usageMode);
	}
}

/// Initializes GPU memory with <size> bytes and the desired access mode
void VertexBuffer::resize(Int32 size, StorageMode mode)
{
	if(mObject)
	{
		GLenum usageMode = getGLUsageMode(mode);		

		glBufferData(GL_ARRAY_BUFFER, size, NULL, usageMode);
	}
}

NEPHILIM_NS_END