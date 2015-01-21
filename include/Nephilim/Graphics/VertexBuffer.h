#ifndef NephilimGraphicsVertexBuffer_h__
#define NephilimGraphicsVertexBuffer_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class VertexArray;


/**
	\class VertexBuffer
	\brief Geometry buffer resource, usually stored in the GPU
*/
class NEPHILIM_API VertexBuffer
{
public:
	enum StorageMode
	{
		StaticDraw,
		StaticCopy,
		StaticRead,
		DynamicDraw,
		DynamicCopy,
		DynamicRead,
		StreamDraw,
		StreamCopy,
		StreamRead
	};

	/// Initializes the vertex buffer to an invalid state
	VertexBuffer();

	/// Make sure the opengl resource has been released and its data
	~VertexBuffer();

	/// Activate this VBO as current
	void bind();

	/// Initializes the vertex buffer to a valid state
	void create();

	/// Eliminate the opengl resource and its data
	void destroy();

	/// Initializes GPU memory with <size> bytes and the desired access mode
	void resize(Int32 size, StorageMode mode);

	/// Upload a VertexArray to the GPU memory
	void upload(const VertexArray& vertexArray, StorageMode mode);

	/// Check if the VBO is valid (initialized)
	operator bool() const;

private:
	unsigned int mObject;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsVertexBuffer_h__
