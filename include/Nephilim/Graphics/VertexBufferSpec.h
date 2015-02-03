#ifndef NephilimVertexBufferSpec_h__
#define NephilimVertexBufferSpec_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class VertexBufferSpec
	\brief Describes a stream of vertex attributes

	This is used exclusively to define what a geometry
	buffer looks like. Using this information, the renderer
	can push the VertexBuffer contents into a draw call.

	There will be one of these objects per type of geometry buffer
	in the engine.

	Note: A vertex buffer spec may contain an actual platform specific 
	implementation attached to it, like VAO in OpenGL 3+, which are needed
	for rendering; In that case, this object will be a part of the rendering 
	pipeline, but otherwise it still helps the renderer do its work on generic
	geometry buffers.
*/
class NEPHILIM_API VertexBufferSpec
{
public:

};

NEPHILIM_NS_END
#endif // NephilimVertexBufferSpec_h__
