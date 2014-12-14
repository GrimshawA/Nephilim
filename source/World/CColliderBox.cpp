#include <Nephilim/World/CColliderBox.h>

NEPHILIM_NS_BEGIN
/// By default, a collider is dynamic and has size 10
CColliderBox::CColliderBox()
: size(10.f, 10.f, 10.f)
, _isDynamic(true)
{

}

/// Construct the collider from a dynamic flag and dimensions
CColliderBox::CColliderBox(bool isDynamic, Vector3D dims)
: size(dims)
, _isDynamic(isDynamic)
{

}
NEPHILIM_NS_END