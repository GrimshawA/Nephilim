#ifndef RenderStateBackup_h__
#define RenderStateBackup_h__

#include <Nephilim/Platform.h>
#include "Matrix.h"

NEPHILIM_NS_BEGIN

class Texture;
class Renderer;

class NEPHILIM_API TextureBackup
{
public:
	TextureBackup();
	~TextureBackup();

	unsigned int id;
};

class NEPHILIM_API RendererTransformBackup
{
public:
	RendererTransformBackup(Renderer* renderer);
	~RendererTransformBackup();

	Renderer* m_renderer;
	mat4 p, v, m;
};

NEPHILIM_NS_END
#endif // RenderStateBackup_h__
