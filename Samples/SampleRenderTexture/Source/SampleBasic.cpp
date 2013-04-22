#include "SampleBasic.h"
#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/MMath.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/UIWindow.h>
#include <Nephilim/Geometry.h>

//#define PROFILER_DISABLE // completely removes all overhead of profiling
#define PROFILER_DEBUG_ONLY
#include <Nephilim/Profiler.h>
#include <Nephilim/Engine.h>

#include "LightingGLSL.h"

#include <iostream>
using namespace std;

Vec2f m_pos(200,200);

bool enableLights = true;

Image img;

Texture t;
Shader ambientPass;
Shader directionalPass;
Shader pointPass;
Shader spotLightPass;
Shader shadowMapPass;
Shader depthRender;

UIWindow ui;

Vec3f cameraEye(0, 4, 15);

struct DirectionalLight
{
	Vec3f direction;
	Vec4f diffuse;
};

struct PointLight
{
	Vec4f position;
	Vec4f diffuse;
};

bool shadowDirty = false;

struct SpotLight
{
	Vec4f position;
	Vec3f direction;
	float cutoff;
	Vec4f diffuse;
};

struct ShadowMap
{
	ShadowMap()
	{
		done = false;
	}
	void activate()
	{
		glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, fbo);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// Always check that our framebuffer is ok
		if(glCheckFramebufferStatusCGL(GL_FRAMEBUFFER_CGL) != GL_FRAMEBUFFER_COMPLETE_CGL)
			cout<<"Failed to create the shadow map."<<endl;
		else
			cout<<"Shadow map created "<<fbo<<endl;

	}
	bool done;
	void prepare()
	{
		if(done) return;

		done = true;

		// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
		GLuint FramebufferName = 0;
		glGenFramebuffersCGL(1, &FramebufferName);
		glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, FramebufferName);

		// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
		
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

		glFramebufferTexture2DCGL(GL_FRAMEBUFFER_CGL, GL_DEPTH_ATTACHMENT_CGL, GL_TEXTURE_2D, depthTexture, 0);

		glDrawBuffer(GL_NONE); // No color buffer is drawn to.

		// Always check that our framebuffer is ok
		if(glCheckFramebufferStatusCGL(GL_FRAMEBUFFER_CGL) != GL_FRAMEBUFFER_COMPLETE_CGL)
			cout<<"Failed to create the shadow map."<<endl;
		else
			cout<<"Shadow map created "<<FramebufferName<<endl;

		fbo = FramebufferName;

	}

	GLuint fbo;
	GLuint depthTexture;
	mat4 projection, view;
};

ShadowMap spotOneShadows;

std::vector<DirectionalLight> dirLights;
std::vector<PointLight> pointLights;
std::vector<SpotLight> spotLights;

void tests()
{
	// lets play with math
	vec4 a;
	a.x = 3;

	mat4 ma;

	Color orange = Color::Orange;
	Color red = Color::Red;
	Color sum = red + orange;

	vec4 floatColor = sum.normalized();

	vec4 r = mat4::rotate(0,0,Math::pi) * mat4::scale(2,2,2) * mat4::identity * mat4::translate(5,1,0) * a;

	cout<< "vec4 "<<r.x<< " "<<r.y<<" "<<r.z<<" "<<r.w<<endl;

	vec3 v = r.xyz();

	if(String("hello world").matches("wor*"))
	{
		cout<<"The string matched the wildcard."<<endl;
	}
}

void regenerateShadowMap();

void drawUi(Renderer* renderer)
{
	renderer->resetShaders();
	renderer->resetTextures();
	ui.draw(renderer);
}

void PortabilityTest::onCreate()
{	
	tests();


	// create ui
	UIControl* control1 = new UIControl(), *control2 = new UIControl(), *control3 = new UIControl();
	control1->setRect(FloatRect(100,100,200,200));
	control1->setProperty<Color>("background-color", Color::Orange);
	control2->setRect(FloatRect(300,300,400,400));
	control2->setProperty<Color>("background-color", Color::Blue);
	control3->setRect(FloatRect(0,0,200,200));
	control3->setProperty<Color>("background-color", Color::Green);
	ui["central"]->addControl(control1);
	ui["central"]->addControl(control2);
	control2->addControl(control3);

	GeometryData cube;
	cube.addBox(30,30,30);




	img.create(100,100, Color(255,10,255));
	t.loadFromImage(img);

	DirectionalLight a,b,c;
	a.diffuse = Vec4f(0.9,0.5,0,1); a.direction = Vec3f(1, 0, 0);
	b.diffuse = Vec4f(0.8,0.3,0.0,1); b.direction = Vec3f(-1, 0, 0);
	c.diffuse = Vec4f(0.7,0.2,0.3,1); c.direction = Vec3f(-0.7, 0, 0.3);
	//dirLights.push_back(a);
	//dirLights.push_back(b);
	//dirLights.push_back(c);

	PointLight ap;
	ap.position = Vec4f(-5, 7, 0, 1);
	ap.diffuse = Vec4f(0.6f, 0.6f, 0.6f, 1.f);
	pointLights.push_back(ap);

	// Camera follower
	PointLight ap2;
	ap2.position = Vec4f(0, 7, 0, 1);
	ap2.diffuse = Vec4f(0.1f, 0.1f, 0.1f, 1.f);
	pointLights.push_back(ap2);

	SpotLight sp1;
	sp1.diffuse = Vec4f(1,0.1,0.1, 1);
	//sp1.direction = Vec3f(0.1, -0.2, -0.7);
	//sp1.position = Vec4f(-4, 7, 8, 1);
	sp1.position = Vec4f(0, 4, 5, 1);
	sp1.direction = sp1.position.xyz() * -1.f;
	sp1.cutoff = cos(Math::pi / 60);
	spotLights.push_back(sp1);

/*	cout << "Engine information" << endl;
	cout << "Version: " << Engine::getVersionString() << endl;
	cout << "OpenGL: " << getGLVersionString() << endl;
	cout << "OpenGL Vendor: " << getGLVendorString() << endl;
	cout << "OpenGL Renderer: " << getGLRendererString() << endl;
	cout<< "Shader information" << endl;
	cout << Shader::getVersion() << endl;
	cout << Shader::getCurrentActiveProgram() << endl;
	cout << endl;

	ShaderGen::prepareDefault(defaultShader);
	*/
	PRINTLOG("Renderer", "Renderer: %s\n", getRenderer()->getName().c_str());

	shadowMapPass.loadShader(Shader::VertexUnit, shadowPassV);
	shadowMapPass.loadShader(Shader::FragmentUnit, shadowPassF);
	shadowMapPass.addAttributeLocation(0, "vertex");
	shadowMapPass.create();

	ambientPass.loadShader(Shader::VertexUnit, ambientPassV);
	ambientPass.loadShader(Shader::FragmentUnit, ambientPassF);
	ambientPass.addAttributeLocation(0, "vertex");
	ambientPass.create();

	directionalPass.loadShader(Shader::VertexUnit, directionalPassV);
	directionalPass.loadShader(Shader::FragmentUnit, directionalPassF);
	directionalPass.addAttributeLocation(0, "vertex");
	directionalPass.addAttributeLocation(1, "normal");
	directionalPass.create();


	pointPass.loadShader(Shader::VertexUnit, pointPassV);
	pointPass.loadShader(Shader::FragmentUnit, pointPassF);
	pointPass.addAttributeLocation(0, "vertex");
	pointPass.addAttributeLocation(1, "normal");
	pointPass.create();

	spotLightPass.loadShader(Shader::VertexUnit, spotlightPassV);
	spotLightPass.loadShader(Shader::FragmentUnit, spotlightPassF);
	spotLightPass.addAttributeLocation(0, "vertex");
	spotLightPass.addAttributeLocation(1, "normal");
	spotLightPass.create();

	depthRender.loadShader(Shader::VertexUnit, depthPassV);
	depthRender.loadShader(Shader::FragmentUnit, depthPassF);
	depthRender.addAttributeLocation(0, "vertex");
	depthRender.addAttributeLocation(2, "uv");
	depthRender.create();



	// Generate the shadow map
}

void PortabilityTest::onEvent(Event &event)
{
    if(event.type == Event::MouseButtonPressed)
    {
		m_pos.x = event.mouseButton.x;

		if(event.mouseButton.button == Mouse::Left)
			cameraEye.x += 1;
		else if(event.mouseButton.button == Mouse::Right)
			cameraEye.x -= 1;
		else if(event.mouseButton.button == Mouse::XButton1)
			cameraEye.y += 1;
		else
			cameraEye.y -= 1;
	}

	if(event.type == Event::MouseWheelMoved)
	{
		//cameraEye.z += event.mouseWheel.delta;
		//cameraEye.y += event.mouseWheel.delta;
		pointLights[0].position.y += event.mouseWheel.delta;
	}

	if(event.type == Event::KeyPressed)
	{
		if(event.key.code == Keyboard::Right)
		{
			pointLights[0].position.x += 1;
		}
		if(event.key.code == Keyboard::Left)
		{
			pointLights[0].position.x -= 1;
		}
		if(event.key.code == Keyboard::Up)
		{
			pointLights[0].position.z += 1;
		}
		if(event.key.code == Keyboard::Down)
		{
			pointLights[0].position.z -= 1;
		}

		if(event.key.code == Keyboard::W)
		{
			cameraEye.z -= 2;
		}

		if(event.key.code == Keyboard::M)
		{
			spotLights[0].position.x += 1;
			spotLights[0].direction = spotLights[0].position.xyz() * -1.f;
			shadowDirty = true;

		}
		if(event.key.code == Keyboard::N)
		{
			spotLights[0].position.x-= 1;
			spotLights[0].direction = spotLights[0].position.xyz() * -1.f;
			shadowDirty = true;
		}if(event.key.code == Keyboard::B)
		{
			spotLights[0].position.z -= 1;
		}

		if(event.key.code == Keyboard::F1)
		{
			enableLights = !enableLights;
		}
	}

}


void PortabilityTest::onUpdate(Time time)
{ 
	// follow
	Vec3f dir = cameraEye - pointLights[1].position.xyz();
	dir.normalize();
	pointLights[1].position += vec4(dir, 1.f) * time.asSeconds();
	//cout<<"position: "<<pointLights[1].position.x<< " "<<pointLights[1].position.y << " "<<pointLights[1].position.z<<endl;

}

class Mesh
{
public:


	void generateBox(Vec3f position = Vec3f(0,0,0), Vec3f size = Vec3f(1,1,1))
	{
		float len = 1;
		float dim = len/2;
		float hx = size.x / 2.f;
		float hy = size.y / 2.f;
		float hz = size.z / 2.f;
		GLfloat vertices[] = {
			-hx,-hy,-hz, hx,-hy,-hz, hx,hy,-hz,   -hx,-hy,-hz,  hx,hy,-hz, -hx, hy,-hz, //back face

			hx,-hy,hz, -hx,hy,hz, -hx,-hy,hz,  hx,-hy,hz,  hx,hy,hz, -hx, hy,hz, //front face

			hx,-hy,-hz,    hx,hy,-hz    , hx,hy,hz    ,  hx,hy,hz,  hx,-hy,hz    , 	hx,-hy,-hz, //right face

			-hx,-hy,-hz, - hx,-hy,hz ,-hx,hy,-hz,  - hx,hy,hz ,-hx,hy,-hz,-hx,-hy,hz, // new left face

			hx,-hy,-hz,   hx,-hy,hz    , -hx, -hy, hz   ,  -hx, -hy, hz, - hx,-hy,-hz    , hx,-hy,-hz, //bottom

			/*-hx,hy,hz,   -hx,hy,-hz    , hx, hy, hz   ,  -hx, hy, -hz, hx,hy,-hz    , hx,hy,hz //top*/
			 -hx,hy,-hz ,  -hx,hy,hz , hx, hy, hz   ,  hx,hy,-hz  ,-hx, hy, -hz  , hx,hy,hz //top


		};

		m_vertices.resize(6 * 6);
		m_normals.resize(6 * 6);
		memcpy(&m_vertices[0], vertices, sizeof(float) * 6 * 6 * 3);
		translation = mat4::translate(position.x, position.y, position.z);

		// generate normals
		for(int i = 0; i < m_vertices.size(); i+=3)
		{
			// triangle is m_vertices[i] .. i+1 i+2
			Vec3f normal(0,0,0);

			Vec3f edge1 = m_vertices[i+1] - m_vertices[i];
			Vec3f edge2 = m_vertices[i+2] - m_vertices[i];
			normal = edge1.cross(edge2);
			normal.normalize();

			m_normals[i] = normal;
			m_normals[i+1] = normal;
			m_normals[i+2] = normal;
		}
	}

	Mesh()
	{
		m_color = Vec4f(0.5, 0.4, 0.1, 1);
	}

	void drawShadow(Renderer* renderer)
	{
		shadowMapPass.setUniformMatrix("model", translation.get());

		renderer->enableVertexAttribArray(0);
		renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
		renderer->drawArrays(Render::Primitive::Triangles, 0, m_vertices.size());
		renderer->disableVertexAttribArray(0);
	}

	void draw(Renderer* renderer)
	{
		// Ambient pass
		ambientPass.bind();
		ambientPass.setUniformMatrix("model", translation.get());
		ambientPass.setUniformVec4("incomingColor", reinterpret_cast<float*>(&m_color));

		renderer->enableVertexAttribArray(0);
		renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
		renderer->drawArrays(Render::Primitive::Triangles, 0, m_vertices.size());
		renderer->disableVertexAttribArray(0);
		
		// Just draw outlines
		/*ambientPass.setUniformVec4("ambient", reinterpret_cast<float*>(&Vec4f(0,0,0,0)));
		renderer->enableVertexAttribArray(0);
		renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
		renderer->drawArrays(Render::Primitive::LineLoop, 0, m_vertices.size());
		renderer->disableVertexAttribArray(0);
		ambientPass.setUniformVec4("ambient", reinterpret_cast<float*>(&Vec4f(1,1,1,1)));*/
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthFunc(GL_EQUAL);

		// Directional pass
		directionalPass.bind();		
		for(int i = 0; i < dirLights.size(); i++)
		{
			directionalPass.setUniformVec4("lightDiffuse", reinterpret_cast<float*>(&dirLights[i].diffuse));
			directionalPass.setUniformVec3("lightDir", reinterpret_cast<float*>(&dirLights[i].direction));
			directionalPass.setUniformMatrix("model", translation.get());

			renderer->enableVertexAttribArray(0);
			renderer->enableVertexAttribArray(1);
			renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
			renderer->setVertexAttribPointer(1, 3, GL_FLOAT, false, 0, &m_normals[0]);
			renderer->drawArrays(Render::Primitive::Triangles, 0, m_vertices.size());
			renderer->disableVertexAttribArray(1);
			renderer->disableVertexAttribArray(0);
		}

		// Point light pass
		pointPass.bind();
		if(enableLights)
		{
			for(int i = 0; i < pointLights.size(); i++)
			{
				pointPass.setUniformVec4("lightDiffuse", reinterpret_cast<float*>(&pointLights[i].diffuse));
				pointPass.setUniformVec4("lightPosition", reinterpret_cast<float*>(&pointLights[i].position));
				pointPass.setUniformMatrix("model", translation.get());

				renderer->enableVertexAttribArray(0);
				renderer->enableVertexAttribArray(1);
				renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
				renderer->setVertexAttribPointer(1, 3, GL_FLOAT, false, 0, &m_normals[0]);
				renderer->drawArrays(Render::Primitive::Triangles, 0, m_vertices.size());
				renderer->disableVertexAttribArray(1);
				renderer->disableVertexAttribArray(0);
		

			}
		}

		// Spot light pass
		spotLightPass.bind();
		if(enableLights)
		{
			for(int i = 0; i < spotLights.size(); i++)
			{
				spotLightPass.setUniformVec4("lightDiffuse", reinterpret_cast<float*>(&spotLights[i].diffuse));
				spotLightPass.setUniformVec4("lightPosition", reinterpret_cast<float*>(&spotLights[i].position));
				spotLightPass.setUniformVec3("lightDirection", reinterpret_cast<float*>(&spotLights[i].direction));
				spotLightPass.setUniformFloat("lightCutoff", spotLights[i].cutoff);
				spotLightPass.setUniformTexture("shadowmap", 0);
				spotLightPass.setUniformMatrix("model", translation.get());
				spotLightPass.setUniformMatrix("shadowp", spotOneShadows.projection.get());
				spotLightPass.setUniformMatrix("shadowv", spotOneShadows.view.get());
				glBindTexture(GL_TEXTURE_2D, spotOneShadows.depthTexture);

				renderer->enableVertexAttribArray(0);
				renderer->enableVertexAttribArray(1);
				renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
				renderer->setVertexAttribPointer(1, 3, GL_FLOAT, false, 0, &m_normals[0]);
				renderer->drawArrays(Render::Primitive::Triangles, 0, m_vertices.size());
				renderer->disableVertexAttribArray(1);
				renderer->disableVertexAttribArray(0);

	

			}
		}
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);

	}

	std::vector<Vec3f> m_vertices;
	std::vector<Vec3f> m_normals;
	Vec4f m_color;

	mat4 translation;
};

std::vector<Mesh> meshes;

void regenerateShadowMap(Renderer* renderer)
{
	glCullFace(GL_FRONT);
	spotOneShadows.prepare();
	spotOneShadows.activate();
	shadowMapPass.bind();

	shadowMapPass.setUniformMatrix("projection", mat4::perspective(45, 1.f, 1.f, 50.f).get());
	shadowMapPass.setUniformMatrix("view", mat4::lookAt(spotLights[0].position.xyz(), Vec4f(spotLights[0].position + Vec4f(spotLights[0].direction, 0.f)).xyz(), Vec3f(0,1,0)).get());
	spotOneShadows.projection = mat4::perspective(45, 1.f, 1.f, 50.f);
	spotOneShadows.view = mat4::lookAt(spotLights[0].position.xyz(), Vec4f(spotLights[0].position + Vec4f(spotLights[0].direction, 0.f)).xyz(), Vec3f(0,1,0));
	
	glViewport(0,0,1024,1024);
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].drawShadow(renderer);
	}
	glCullFace(GL_BACK);
	glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
	
	shadowDirty = false;
}


void PortabilityTest::onRender()
{
	//glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glDisable(GL_DITHER);


	if(shadowDirty)
	{
		regenerateShadowMap(getRenderer());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	// 3D scene for lighting
	static bool inited = false;
	if(!inited)
	{
		Mesh base;
		Mesh house;
		Mesh lamp;
		Mesh crate;
		Mesh backWall;

		base.generateBox(Vec3f(0, -1, 0), Vec3f(50, 2, 50));
		house.generateBox(Vec3f(0, 1, 0), Vec3f(6, 5, 3));
		backWall.generateBox(Vec3f(0, -2, -18), Vec3f(15, 10, 2));
		lamp.generateBox(Vec3f(4, 3, 1), Vec3f(1,6,1));
		crate.generateBox(Vec3f(0,5,4), Vec3f(1,1,1));

		house.m_color = Vec4f(0.1, 0.1, 0.1, 1);
		base.m_color = Vec4f(0.3,0.4,0.3, 1);

		meshes.push_back(base);
		meshes.push_back(house);
		meshes.push_back(lamp);
		meshes.push_back(crate);
		meshes.push_back(backWall);

		regenerateShadowMap(getRenderer());

		inited = true;
	}




	mat4 sceneProjection = mat4::perspective(45.f, 1024.f / 768.f, 1, 10000);
	mat4 sceneCamera = mat4::lookAt(cameraEye, Vec3f(0,0,0), Vec3f(0,1,0));
	//sceneProjection =  mat4::perspective(45, 1.f, 1.f, 50.f);
	//sceneCamera = mat4::lookAt(spotLights[0].position.xyz(), Vec4f(spotLights[0].position + Vec4f(spotLights[0].direction, 0.f)).xyz(), Vec3f(0,1,0));



	// Camera setup for ambient pass
	ambientPass.bind();
	ambientPass.setUniformMatrix("projection", sceneProjection.get() );
	ambientPass.setUniformMatrix("view",  sceneCamera.get());
	directionalPass.bind();
	directionalPass.setUniformMatrix("projection", sceneProjection.get() );
	directionalPass.setUniformMatrix("view", sceneCamera.get());
	pointPass.bind();
	pointPass.setUniformMatrix("projection", sceneProjection.get() );
	pointPass.setUniformMatrix("view", sceneCamera.get());
	spotLightPass.bind();
	spotLightPass.setUniformMatrix("projection", sceneProjection.get() );
	spotLightPass.setUniformMatrix("view", sceneCamera.get());

	// Draw lit all of them
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(getRenderer());
	}

	if(pointLights.size() > 0)
	{
		Mesh pointLightDebug;pointLightDebug.m_color = Vec4f(0.1,0.1,0.1,1);pointLightDebug.generateBox(Vec3f(pointLights[0].position.x,pointLights[0].position.y,pointLights[0].position.z), Vec3f(0.3,0.3, 0.3)); pointLightDebug.draw(getRenderer());
	}

	glDisable(GL_CULL_FACE);
	ambientPass.bind();
	glPointSize(8.f);
	GeometryData geom;
	geom << TorusDef(4, 30);
	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &geom.m_vertices[0]);
	getRenderer()->drawArrays(Render::Primitive::Points, 0, geom.m_vertices.size());
	getRenderer()->disableVertexAttribArray(0);

	/*
	depthRender.bind();

	static const GLfloat g_quad_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
	};

	glBindTexture(GL_TEXTURE_2D, spotOneShadows.depthTexture);
	glViewport(0,0,300,300);
	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->setVertexAttribPointer(0,3, GL_FLOAT, false, 0, g_quad_vertex_buffer_data);
	getRenderer()->drawArrays(Render::Primitive::Triangles, 0, 6);
	glViewport(0,0,1024,768);*/

	drawUi(getRenderer());

}
