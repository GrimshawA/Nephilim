#include <Nephilim/BxDraw.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

BxDraw::BxDraw()
{
	line.m_primitive = Render::Primitive::Lines;
	line.m_vertices.push_back(vec3());
	line.m_vertices.push_back(vec3());
}


void BxDraw::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
	line.m_vertices[0] = vec3(from.getX(), from.getY(), from.getZ());
	line.m_vertices[1] = vec3(to.getX(), to.getY(), to.getZ());

	renderer->draw(line);
}

void BxDraw::drawTriangle(const btVector3 &a, const btVector3 &b, const btVector3 &c, const btVector3 &color, btScalar alpha)
{

}
void BxDraw::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{

}
void BxDraw::reportErrorWarning(const char *warningString)
{

}

void BxDraw::draw3dText(const btVector3 &location, const char *textString)
{

}
void BxDraw::setDebugMode(int debugMode)
{
	this->debugMode = debugMode;
}
int BxDraw::getDebugMode() const
{
	return debugMode;
}

NEPHILIM_NS_END