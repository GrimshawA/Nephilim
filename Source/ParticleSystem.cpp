#include <Nephilim/ParticleSystem.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Image.h>
#include <Nephilim/MMath.h>

NEPHILIM_NS_BEGIN

ParticleSystem::ParticleSystem()
{
	
}

void ParticleSystem::create()
{
	Image im;
	im.loadFromFile("part.png");
	im.createMaskFromColor(Color::Black, 0);
	tex.loadFromImage(im);
}


void ParticleSystem::update(float deltaTime)
{
	Sprite sprite;
	sprite.setPosition(Math::random(30,500),Math::random(40,500));
	sprite.setTexture(tex);
	sprite.setColor(Color(Math::randomInt(1,255), Math::randomInt(1,200), Math::randomInt(1,170)));
	m_particles.push_back(sprite);
}

void ParticleSystem::onDraw(Renderer* renderer)
{
	renderer->setDefaultBlending();
	for(int i =0; i < m_particles.size(); i++)
	{
		renderer->draw(m_particles[i]);
	}
}


NEPHILIM_NS_END
