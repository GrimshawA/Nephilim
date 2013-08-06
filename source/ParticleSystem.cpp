#include <Nephilim/ParticleSystem.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Image.h>
#include <Nephilim/MMath.h>

NEPHILIM_NS_BEGIN

ParticleSystem::ParticleSystem()
: counter(0)
{
	
}

void ParticleSystem::create()
{
	tex = new Texture();
	tex->loadFromFile("part.png");

	position = vec3(400,400,0);
}


void ParticleSystem::update(float deltaTime)
{
	for(int i =0; i < m_particles.size(); i++)
	{
		m_particles[i].position += m_particles[i].velocity * deltaTime;
		m_particles[i].s.setPosition(m_particles[i].position.x, m_particles[i].position.y);
	}


	if(++counter % 2 == 0)
	{
		Sprite sprite;
		sprite.setPosition(position.x,position.y);
		sprite.setTexture(*tex);
		sprite.setOrigin(32,32);
		sprite.setColor(Color(math::randomInt(1,250), math::randomInt(100,200), math::randomInt(1,140)));
		sprite.resize(32,32);
		Particle pp;
		pp.position  = vec3(position.x,position.y,0);
		//float angle = Math::random(0, Math::pi*2); pp.velocity = vec3(cos(angle) * 80, sin(angle)*80,0);
		pp.s = sprite;
		m_particles.push_back(pp);
	}
	

	if(m_particles.size() > tank)
		m_particles.erase(m_particles.begin());
}

void ParticleSystem::onDraw(Renderer* renderer)
{
	renderer->setBlendMode(Render::Blend::Alpha);
	for(int i =0; i < m_particles.size(); i++)
	{
		renderer->draw(m_particles[i].s);
	}
	renderer->setDefaultBlending();

}


NEPHILIM_NS_END
