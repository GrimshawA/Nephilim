#include <Nephilim/Foundation/Transform2.h>
#include <Nephilim/Foundation/Logging.h>

#include <cmath>

NEPHILIM_NS_BEGIN
////////////////////////////////////////////////////////////
const Transform2 Transform2::Identity;


////////////////////////////////////////////////////////////
Transform2::Transform2()
{
    // Identity matrix
    m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8]  = 0.f; m_matrix[12] = 0.f;
    m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9]  = 0.f; m_matrix[13] = 0.f;
    m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
    m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
}


////////////////////////////////////////////////////////////
Transform2::Transform2(float a00, float a01, float a02,
                     float a10, float a11, float a12,
                     float a20, float a21, float a22)
{
    m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8]  = 0.f; m_matrix[12] = a02;
    m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9]  = 0.f; m_matrix[13] = a12;
    m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
    m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0.f; m_matrix[15] = a22;
}


////////////////////////////////////////////////////////////
const float* Transform2::getMatrix() const
{
    return m_matrix;
}


////////////////////////////////////////////////////////////
Transform2 Transform2::getInverse() const
{
    // Compute the determinant
    float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
                m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
                m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

	Log("COMPUTED DET %f in VIEW", det);

    // Compute the inverse if the determinant is not zero
    // (don't use an epsilon because the determinant may *really* be tiny)
    if (det != 0.f)
    {
        return Transform2( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                         -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                          (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                         -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                          (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                         -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                          (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                         -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                          (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    }
    else
    {
        return Identity;
    }
}


////////////////////////////////////////////////////////////
Vec2f Transform2::transformPoint(float x, float y) const
{
    return Vec2f(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
                    m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
}


////////////////////////////////////////////////////////////
Vec2f Transform2::transformPoint(const Vec2f& point) const
{
    return transformPoint(point.x, point.y);
}


////////////////////////////////////////////////////////////
FloatRect Transform2::transformRect(const FloatRect& rectangle) const
{
    // Transform the 4 corners of the rectangle
    const Vec2f points[] =
    {
        transformPoint(rectangle.left, rectangle.top),
        transformPoint(rectangle.left, rectangle.top + rectangle.height),
        transformPoint(rectangle.left + rectangle.width, rectangle.top),
        transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
    };

    // Compute the bounding rectangle of the transformed points
    float left = points[0].x;
    float top = points[0].y;
    float right = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i)
    {
        if      (points[i].x < left)   left = points[i].x;
        else if (points[i].x > right)  right = points[i].x;
        if      (points[i].y < top)    top = points[i].y;
        else if (points[i].y > bottom) bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::combine(const Transform2& transform)
{
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    *this = Transform2(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                      a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                      a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                      a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                      a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                      a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                      a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                      a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                      a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

    return *this;
}


////////////////////////////////////////////////////////////
Transform2& Transform2::translate(float x, float y)
{
    Transform2 translation(1, 0, x,
                          0, 1, y,
                          0, 0, 1);

    return combine(translation);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::translate(const Vec2f& offset)
{
    return translate(offset.x, offset.y);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::rotate(float angle)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform2 rotation(cos, -sin, 0,
                       sin,  cos, 0,
                       0,    0,   1);

    return combine(rotation);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::rotate(float angle, float centerX, float centerY)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform2 rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
                       sin,  cos, centerY * (1 - cos) - centerX * sin,
                       0,    0,   1);

    return combine(rotation);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::rotate(float angle, const Vec2f& center)
{
    return rotate(angle, center.x, center.y);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::scale(float scaleX, float scaleY)
{
    Transform2 scaling(scaleX, 0,      0,
                      0,      scaleY, 0,
                      0,      0,      1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::scale(float scaleX, float scaleY, float centerX, float centerY)
{
    Transform2 scaling(scaleX, 0,      centerX * (1 - scaleX),
                      0,      scaleY, centerY * (1 - scaleY),
                      0,      0,      1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::scale(const Vec2f& factors)
{
    return scale(factors.x, factors.y);
}


////////////////////////////////////////////////////////////
Transform2& Transform2::scale(const Vec2f& factors, const Vec2f& center)
{
    return scale(factors.x, factors.y, center.x, center.y);
}


////////////////////////////////////////////////////////////
Transform2 operator *(const Transform2& left, const Transform2& right)
{
    return Transform2(left).combine(right);
}

////////////////////////////////////////////////////////////
Transform2& operator *=(Transform2& left, const Transform2& right)
{
    return left.combine(right);
}


////////////////////////////////////////////////////////////
Vec2f operator *(const Transform2& left, const Vec2f& right)
{
    return left.transformPoint(right);
}

NEPHILIM_NS_END
