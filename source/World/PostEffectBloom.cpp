#include <Nephilim/World/PostEffectBloom.h>
#include <Nephilim/Graphics/GL/GLTexture.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Graphics/VertexArray2D.h>
#include <Nephilim/Graphics/Shader.h>

#include <Nephilim/Foundation/Logging.h>

#include <Nephilim/Foundation/File.h>



NEPHILIM_NS_BEGIN

String getFile(const String& filename)
{
	String s = "";

	File f(filename, IODevice::TextRead);
	if(f)
	{
		while(!f.atEnd())
		{
			s += f.getChar();
		}
	}

	return s;
}

PostEffectBloom::PostEffectBloom()
{
	/*mBrightnessShader.loadShader(Shader::VertexUnit, getFile("shaders/Fullpass.vert"));
	mBrightnessShader.loadShader(Shader::FragmentUnit, getFile("shaders/Brightness.frag"));
	mBrightnessShader.addAttributeLocation(0, "vertex");
	mBrightnessShader.addAttributeLocation(1, "color");
	mBrightnessShader.addAttributeLocation(2, "texCoord");
	mBrightnessShader.create();

	// Prepare textures
	mBrightnessTexture.create(1000.f, 500.f);
	mBrightnessTexture.setSmooth(true);
	mBrightnessFramebuffer.create();
	mBrightnessFramebuffer.activate();
	mBrightnessFramebuffer.attachTexture(mBrightnessTexture);

	mFirstPassTextures[0].create(1000.f / 2, 500.f / 2);
	mFirstPassTextures[0].setSmooth(true);
	mFirstPassTextures[1].create(1000.f / 2, 500.f / 2);
	mFirstPassTextures[1].setSmooth(true);

	mSecondPassTextures[0].create(1000.f / 4, 500.f / 4);
	mSecondPassTextures[0].setSmooth(true);
	mSecondPassTextures[1].create(1000.f / 4, 500.f / 4);
	mSecondPassTextures[1].setSmooth(true);*/
}

void PostEffectBloom::apply(GraphicsDevice* renderer, Texture& renderTexture)
{
	
	// After the brightness pass operation, mBrightnessTexture contains the output of the scene
	renderTexture.bind();
	brightnessPass(renderer);

	// Draw the brightness pass texture to the screen
	renderer->setDefaultTarget();
	renderer->setDefaultShader();
	renderer->setProjectionMatrix(View(0, 0, 1000, 500).getMatrix());
	renderer->setViewMatrix(mat4::identity);
	renderer->setDefaultViewport();
	renderer->setDepthTestEnabled(false);
	RectangleShape finalComposite;
	finalComposite.setTexture(&mBrightnessTexture);
	finalComposite.invertTextureCoordinates();
	finalComposite.setSize(1000.f, 500.f);
	//finalComposite.setColor(Color::Grass);
	renderer->draw(finalComposite);
}

void PostEffectBloom::brightnessPass(GraphicsDevice* mRenderer)
{
	// Trigger the right shader
	Shader s;
	s.shaderImpl = &mBrightnessShader;
	mRenderer->setShader(s);

	mBrightnessFramebuffer.activate(); // activate drawing to the brightness texture
	Log("Rendering the brightness pass with shader %d", mBrightnessShader.getIdentifier());
	mBrightnessShader.setUniformTexture("source", 0);

	mRenderer->clearColorBuffer();
	mRenderer->setProjectionMatrix(View(0, 0, 1000, 500).getMatrix());
	mRenderer->setViewMatrix(mat4::identity);
	mRenderer->setModelMatrix(mat4::identity);

	VertexArray2D vertices(Render::Primitive::TriangleStrip, 4);
	vertices[0] = VertexArray2D::Vertex(vec2(0, 0),    Color::White,        vec2(0, 1));
	vertices[1] = VertexArray2D::Vertex(vec2(1000.f, 0),Color::White,       vec2(1, 1));
	vertices[2] = VertexArray2D::Vertex(vec2(0, 500.f), Color::White,      vec2(0, 0));
	vertices[3] = VertexArray2D::Vertex(vec2(1000.f, 500.f),   Color::White,         vec2(1, 0));
	mRenderer->draw(vertices);

	//RectangleShape r(FloatRect(0,0,1000,500), Color::Red);
	//mRenderer->draw(r);
}

NEPHILIM_NS_END