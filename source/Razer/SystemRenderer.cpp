#include <Nephilim/Razer/SystemRenderer.h>
#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/Entity.inl>
#include <Nephilim/Razer/ComponentTilemap2D.h>
#include <Nephilim/Razer/ComponentTerrain.h>
#include <Nephilim/Razer/ComponentCamera.h>
#include <Nephilim/Razer/ComponentSprite.h>
#include <Nephilim/Razer/ComponentTransform.h>
#include <Nephilim/Razer/ComponentParticleEmitter.h>
#include <Nephilim/Razer/ComponentMesh.h>
#include <Nephilim/Razer/SystemKinesis2D.h>

#include <Nephilim/Logger.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/CGL.h>

#include <Nephilim/Razer/PostEffectBloom.h>

NEPHILIM_NS_BEGIN
namespace rzr{
	
SystemRenderer::SystemRenderer()
: System()
, mRenderer(NULL)
, mContentManager(NULL)
{
	// add a test bloom effect
	mPostEffects.push_back(new PostEffectBloom);

	// init the render to texture
	mRenderTexture.create(1000.f, 500.f);
	if(mFramebuffer.create())
	{
		mFramebuffer.activate();
		mFramebuffer.attachTexture(mRenderTexture);

		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1000, 500);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Log("=>>>>>>>>> Render Texture created");
	}
	else
	{
		Log(">>>>>>>>>>> Could not make render texture");
	}
	
}

void SystemRenderer::render()
{
	// Bind render to texture
	//mFramebuffer.activate();
	//glViewport(0, 0, 1000, 500);

	// Find a camera
	for(size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentCamera>())
		{
			ComponentCamera& camera = ent.getComponent<ComponentCamera>();
			ComponentTransform& transform = ent.getComponent<ComponentTransform>();

			// Let's compute this camera transform
			camera.cameraTransform = mat4::identity;
			camera.cameraTransform = transform.rotation.toMatrix() * mat4::translate(-transform.x, -transform.y, -transform.z);

			mRenderer->setProjectionMatrix(mat4::perspective(65.f, 1000.f / 500.f, 5.f, 3000.f));
		//	mRenderer->setViewMatrix(mat4::lookAt(vec3(camera.x, camera.y, camera.z), vec3(camera.center_x, camera.center_y, camera.center_z) , camera.up));
			mRenderer->setViewMatrix(camera.cameraTransform);
			mRenderer->clearDepthBuffer();
			mRenderer->setDepthTestEnabled(false);
			mRenderer->clearColorBuffer();
			mRenderer->setBlendingEnabled(true);
			mRenderer->setBlendMode(Render::Blend::Alpha);
		}
	}

	// Render each entity
	for(size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentTilemap2D>())
		{
			renderTilemap(ent);
		}
		if(ent.hasComponent<ComponentTerrain>())
		{
			ent.getComponent<ComponentTerrain>().surfaceTex.bind();
			mRenderer->draw(ent.getComponent<ComponentTerrain>().geometry);
		}
		if(ent.hasComponent<ComponentMesh>()) 
		{
			mRenderer->setDepthTestEnabled(true);
			renderMesh(ent);
		}
		if(ent.hasComponent<ComponentSprite>()) 
		{
			mRenderer->setDepthTestEnabled(false);

			ComponentTransform& transform = ent.getComponent<ComponentTransform>();
			ComponentSprite& sprite = ent.getComponent<ComponentSprite>();


			RectangleShape spr;
			spr.setPosition(transform.x, transform.y);
			spr.setSize(sprite.width, sprite.height);
			spr.setOrigin(spr.getSize() / 2.f);
			spr.setScale(sprite.scale.x, sprite.scale.y);
			if(!sprite.tex.empty())
			{
				spr.setTexture(mContentManager->getTexture(sprite.tex));
				if(sprite.tex_rect_size.x > 0 && sprite.tex_rect_size.y > 0)
				{
					spr.setTextureRect(sprite.tex_rect_pos.x, sprite.tex_rect_pos.y, sprite.tex_rect_size.x, sprite.tex_rect_size.y);
				}
				spr.invertTextureCoordinates();
			}
			mRenderer->draw(spr);
			mRenderer->setDefaultTexture();
			mRenderer->setModelMatrix(mat4::identity);

		}
		if(ent.hasComponent<ComponentParticleEmitter>()) 
		{
			mRenderer->setDepthTestEnabled(false);
			ComponentParticleEmitter& emitter = ent.getComponent<ComponentParticleEmitter>();

			mRenderer->setBlendingEnabled(true);
			mRenderer->setBlendMode(Render::Blend::AddAlpha);
			mRenderer->setDepthTestEnabled(false);
			for(size_t j = 0; j < emitter.particles.size(); ++j)
			{
				mRenderer->draw(emitter.particles[j].mSprite);
			}
			mRenderer->setBlendMode(Render::Blend::Alpha);
		//	Log("rendering particles");
		}
	}

//	KxDraw dr(((SystemKinesis2D*)mScene->mRegisteredSystems[0])->mScene);
	//mRenderer->draw(dr);

	// Post processing
	//((PostEffectBloom*)mPostEffects[0])->apply(mRenderer, mRenderTexture);

	/*mRenderer->setDefaultTarget();
	mRenderer->setDefaultShader();
	mRenderer->setProjectionMatrix(View(0, 0, 1000, 500).getMatrix());
	mRenderer->setViewMatrix(mat4::identity);
	mRenderer->setDefaultViewport();
	mRenderer->setDepthTestEnabled(false);

	RectangleShape finalComposite;
	finalComposite.setTexture(&mRenderTexture);
	finalComposite.invertTextureCoordinates();
	finalComposite.setSize(1000.f, 500.f);
	//finalComposite.setColor(Color::Blue);
	mRenderer->draw(finalComposite);*/
}

void SystemRenderer::renderMesh(Entity& entity)
{
	ComponentMesh& mesh = entity.getComponent<ComponentMesh>();

	if(!mesh.mVertexBuffer)
	{
		Log("====>>> Uploading geometry to the VBO");
		mesh.mVertexBuffer.create();
		mesh.mVertexBuffer.bind();
		mesh.mVertexBuffer.upload(mesh.mVertexArray, VertexBuffer::StaticDraw);
	}

	// Draw the mesh
	if(mesh.mIndexArray.indices.size() > 0)
	{
		static Texture myTex;

		static bool loaded = false;

		if(!loaded)
		{
			myTex.loadFromFile("textures/wood.png");
			loaded = true;
		}

		myTex.bind();

		//mRenderer->setDefaultTexture();
		mRenderer->setModelMatrix(mat4::identity);

		mRenderer->enableVertexAttribArray(0);
		mRenderer->enableVertexAttribArray(1);
		mRenderer->enableVertexAttribArray(2);

		//mRenderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(0));
		//mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(1));
		//mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(2));


		// with vertex buffer
		mesh.mVertexBuffer.bind();
		mRenderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), static_cast<char*>(NULL) + mesh.mVertexArray.getAttributeOffset(0));
		mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), static_cast<char*>(NULL) + mesh.mVertexArray.getAttributeOffset(1));
		mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), static_cast<char*>(NULL) + mesh.mVertexArray.getAttributeOffset(2));
		
		glDrawElements(GL_TRIANGLES, mesh.mIndexArray.indices.size(), GL_UNSIGNED_SHORT, &mesh.mIndexArray.indices[0]);

		mRenderer->disableVertexAttribArray(0);
		mRenderer->disableVertexAttribArray(1);
		mRenderer->disableVertexAttribArray(2);
	}
}

void SystemRenderer::renderTilemap(Entity& entity)
{
	static Texture myTex;

	static bool loaded = false;

	if(!loaded)
	{
		myTex.loadFromFile("textures/tmw_desert_spacing.png");
		loaded = true;
	}

	myTex.bind();

	if(entity.hasComponent<ComponentTilemap2D>())
	{
		ComponentTilemap2D& tilemap = entity.getComponent<ComponentTilemap2D>();

		mRenderer->setModelMatrix(mat4::translate(+500, 0, 0));

		for(size_t j = 0; j < tilemap.mLayers.size(); ++j)
		{
			if(tilemap.mLayers[j].mName == "LevelData")
			{
				mRenderer->enableVertexAttribArray(0);
				mRenderer->enableVertexAttribArray(1);
				mRenderer->enableVertexAttribArray(2);

				mRenderer->setVertexAttribPointer(0, 2, GL_FLOAT, false, tilemap.mLayers[j].mVertexData.getVertexSize(), &tilemap.mLayers[j].mVertexData.data[0] + tilemap.mLayers[j].mVertexData.getAttributeOffset(0));
				mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, tilemap.mLayers[j].mVertexData.getVertexSize(), &tilemap.mLayers[j].mVertexData.data[0] + tilemap.mLayers[j].mVertexData.getAttributeOffset(1));
				mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, tilemap.mLayers[j].mVertexData.getVertexSize(), &tilemap.mLayers[j].mVertexData.data[0] + tilemap.mLayers[j].mVertexData.getAttributeOffset(2));

				glDrawElements(GL_TRIANGLES, tilemap.mLayers[j].mIndexData.indices.size(), GL_UNSIGNED_SHORT, &tilemap.mLayers[j].mIndexData.indices[0]);

				mRenderer->disableVertexAttribArray(0);
				mRenderer->disableVertexAttribArray(1);
				mRenderer->disableVertexAttribArray(2);
			}				
		}
	}
}


};
NEPHILIM_NS_END