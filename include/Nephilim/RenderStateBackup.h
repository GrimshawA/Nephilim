#ifndef RenderStateBackup_h__
#define RenderStateBackup_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

class Texture;

class NEPHILIM_API TextureBackup
{
public:
	TextureBackup();
	~TextureBackup();

	unsigned int id;
};

NEPHILIM_NS_END
#endif // RenderStateBackup_h__
