#include <Nephilim/Graphics/Texture2D.h>

NEPHILIM_NS_BEGIN

/// Construct the uninitialized texture
Texture2D::Texture2D()
: _impl(nullptr)
{
}

/// Ensure destruction of the resource
Texture2D::~Texture2D()
{
}

NEPHILIM_NS_END