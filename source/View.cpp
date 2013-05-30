#include <Nephilim/View.h>
#include <Nephilim/NxMath.h>

#include <cmath>

NEPHILIM_NS_BEGIN

View::View()
: m_transformUpdated(false)
, m_invTransformUpdated(false)
, m_rotation(0.f)
, m_viewport(0.f,0.f,1.f,1.f)
{

}

View::View(float left, float top, float width, float height)
: m_transformUpdated(false), m_invTransformUpdated(false), m_rotation(0.f), m_viewport(0.f,0.f,1.f,1.f)
{
	setRect(left, top, width, height);
}

/// Set a rotation for the view
void View::setRotation(float angle)
{
	m_rotation = angle;
}

/// Get the projection matrix of this view
mat4 View::getMatrix()
{
	return mat4(getTransform().getMatrix());
}

/// Get the view center
Vec2f View::getCenter(){
	return Vec2f(m_rect.left + m_rect.width/2, m_rect.top + m_rect.height/2);
};

void View::move(float x, float y){
	 setCenter(m_center.x + x, m_center.y + y);
};

/// Rotate the view by the given degree angle
void View::rotate(float degrees){
	m_rotation += degrees;
};

FloatRect View::getViewport() const{
	return m_viewport;
};

void View::setViewport(FloatRect viewport){
	m_viewport = viewport;
};


/// Set the view center as a position
void View::setCenter(Vec2f position){
	m_center = position;
	m_rect.set(position.x - m_rect.width/2, position.y - m_rect.height/2, m_rect.width, m_rect.height);

	m_transformUpdated = false;
	m_invTransformUpdated = false;
};

/// Set the view center as a position
void View::setCenter(float x, float y){
	setCenter(Vec2f(x,y));
};


/// Set the viewport from one of the presets
void View::setViewportPreset(int preset){
	switch((ViewportPreset)preset){
		case TopLeftQuarter:
			{
				//setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
			}
			break;
		case TopRightQuarter:
			{
				//setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
			}
			break;
		case BottomLeftQuarter:
			{
				//setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case BottomRightQuarter:
			{
				//setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
			}
			break;
		case TopHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.5f));
			}
			break;
		case BottomHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.5f, 1.f, 0.5f));
			}
			break;
		case LeftHalf:
			{
				//setViewport(sf::FloatRect(0.f, 0.0f, 0.5f, 1.f));
			}
			break;
		case RightHalf:
			{
				//setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.0f));
			}
			break;
		case WideScreen:
			{
				//setViewport(sf::FloatRect(0.f, 0.08f, 1.f, 0.92f));
			}
			break;
	}
};

FloatRect View::getRect() const{
	return m_rect;
};


/// Reset the view to this rect
void View::setRect(float x, float y, float width, float height){
	//reset(sf::FloatRect(x, y, width, height));
	m_rect.left = x;
	m_rect.top = y;
	m_rect.width = width;
	m_rect.height = height;
	m_center = Vec2f(m_rect.left + m_rect.width/2, m_rect.top + m_rect.height/2);

	m_transformUpdated = false;
	m_invTransformUpdated = false;
};

/// Get the dimensions of the view rect
Vec2f View::getSize(){
	return Vec2f(m_rect.width, m_rect.height);
};

/// Set the size of the view rect, perserving its center
void View::setSize(float width, float height){
	m_rect.left = getCenter().x - width/2;
	m_rect.top = getCenter().y - height/2;
	m_rect.width = width;
	m_rect.height = height;
	m_center.x = m_rect.left + m_rect.width/2;
	m_center.y = m_rect.top + m_rect.height/2;

	m_transformUpdated = false;
	m_invTransformUpdated = false;
};

/// Zoom the view by a factor
void View::zoom(float factor){
	setSize(getSize().x * factor , getSize().y * factor);

	m_transformUpdated = false;
	m_invTransformUpdated = false;
};

////////////////////////////////////////////////////////////
const Transform& View::getTransform() const
{
	// Recompute the matrix if needed
	if (!m_transformUpdated)
	{
		// Rotation components
		m_center = Vec2f(m_rect.left + (m_rect.width / 2), m_rect.top + (m_rect.height / 2));
		Vec2f m_size(m_rect.width,m_rect.height);

		float angle  = m_rotation * 3.141592654f / 180.f;
		float cosine = static_cast<float>(std::cos(angle));
		float sine   = static_cast<float>(std::sin(angle));
		float tx     = -m_center.x * cosine - m_center.y * sine + m_center.x;
		float ty     =  m_center.x * sine - m_center.y * cosine + m_center.y;

		// Projection components
		float a =  2.f / m_size.x;
		float b = -2.f / m_size.y;
		float c = -a * m_center.x;
		float d = -b * m_center.y;

		// Rebuild the projection matrix
		m_transform = Transform( a * cosine, a * sine,   a * tx + c,
			-b * sine,   b * cosine, b * ty + d,
			0.f,        0.f,        1.f);
		m_transformUpdated = true;
	}

	return m_transform;
}


////////////////////////////////////////////////////////////
const Transform& View::getInverseTransform() const
{
	// Recompute the matrix if needed
	if (!m_invTransformUpdated)
	{
		m_inverseTransform = getTransform().getInverse();
		m_invTransformUpdated = true; 
	}

	return m_inverseTransform;
}


NEPHILIM_NS_END