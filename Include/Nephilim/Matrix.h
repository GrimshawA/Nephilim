#ifndef Matrix_h__
#define Matrix_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class mat4
	\brief 4x4 Matrix oriented for OpenGL transformations

	Note: Row major
*/
class NEPHILIM_API mat4
{
public:
	/// Construct the matrix with identity
	mat4();

	/// Get the matrix array ptr
	const float* get();

private:
	float m_matrix[16]; ///< The matrix array
};

NEPHILIM_NS_END
#endif // Matrix_h__
