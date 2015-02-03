#ifndef NephilimGraphicsVertexBuffer_h__
#define NephilimGraphicsVertexBuffer_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class GDI_VertexBuffer;

/**
	\class VertexBuffer
	\brief Geometry buffer resource, usually stored in the GPU

	VertexBuffer isn't inherited directly by the low level implementation,
	it holds a implementation pointer inside, so anyone can inherit VertexBuffer
	to maintain easier a given vertex format and possible utilities like streaming 
	contents into the buffer etc.
*/
class NEPHILIM_API VertexBuffer
{
public:

	/// The low level vertex buffer resource
	GDI_VertexBuffer* _impl = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsVertexBuffer_h__
