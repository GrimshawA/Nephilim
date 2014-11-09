#include <Nephilim/Graphics/IndexBuffer.h>
#include <Nephilim/CGL.h>

NEPHILIM_NS_BEGIN

/// Initializes the vertex buffer to an invalid state
IndexBuffer::IndexBuffer()
: mObject(0)
{
}

/// Make sure the opengl resource has been released and its data
IndexBuffer::~IndexBuffer()
{
	destroy();
}

/// Initializes the vertex buffer to a valid state
void IndexBuffer::create()
{
	// Don't initialize unless there is nothing previously allocated
	if(mObject == 0)
	{
		glGenBuffers(1, &mObject);
	}
}

/// Eliminate the opengl resource and its data
void IndexBuffer::destroy()
{
	if(mObject)
	{
		glDeleteBuffers(1, &mObject);
		mObject = 0;
	}
}

/// Provisory: Binds the VBO as an index buffer for indices
void IndexBuffer::bind()
{
	if(mObject > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mObject);
	}
}

NEPHILIM_NS_END