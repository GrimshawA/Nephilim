#include <Nephilim/Razer/ComponentCamera.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

ComponentCamera::ComponentCamera()
: up(0.f, 1.f, 0.f)
, eye(0.f, 20.f, 20.f)
, position(0.f, 0.f, 0.f)
, x(0.f)
, y(20.f)
, z(20.f)
{

}


};
NEPHILIM_NS_END
