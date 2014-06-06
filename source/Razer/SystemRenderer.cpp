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
#include <Nephilim/Path.h>
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
			camera.cameraTransform = transform.rotation.toMatrix() * mat4::translate(-transform.position.x, -transform.position.y, -transform.position.z);

			if(camera.mOrtho)
			{
				float zoom = 1.f / transform.position.z;
				mRenderer->setProjectionMatrix(mat4::ortho(0, 1000.f * zoom, 0, 500.f * zoom, camera.zNear, camera.zFar));
			}
			else
			{
				mRenderer->setProjectionMatrix(mat4::perspective(10.f, 1000.f / 500.f, camera.zNear, camera.zFar));
			}
			mRenderer->setViewMatrix(camera.cameraTransform);
			mRenderer->clearDepthBuffer();
			mRenderer->setDepthTestEnabled(false);
			mRenderer->clearColorBuffer();
			mRenderer->setBlendingEnabled(true);
			mRenderer->setBlendMode(Render::Blend::Alpha);

			// debug
			//View v(0, 0, 20, 10); v.setCenter((int)transform.position.x, (int)transform.position.y);
			//mRenderer->setProjectionMatrix(v.getMatrix());
			//mRenderer->setViewMatrix(mat4::identity);

			//mRenderer->setProjectionMatrix(mat4::ortho(0, 20, 0, 10, 1, 3000));
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
			spr.setPosition(transform.position.x, transform.position.y);
			spr.setSize(sprite.width, sprite.height);
			spr.setOrigin(spr.getSize() / 2.f);
			spr.setScale(sprite.scale.x, sprite.scale.y);
			if(!sprite.tex.empty())
			{
				//Log("Rendering ship sprite: %s", sprite.tex.c_str());

				spr.setTexture(mContentManager->getTexture(sprite.tex));
				if(sprite.tex_rect_size.x > 0 && sprite.tex_rect_size.y > 0)
				{
					//Log("Texture coords: %f, %f, %f, %f", sprite.tex_rect_pos.x, sprite.tex_rect_pos.y, sprite.tex_rect_size.x, sprite.tex_rect_size.y);
					spr.setTextureRect(sprite.tex_rect_pos.x, sprite.tex_rect_pos.y, sprite.tex_rect_size.x, sprite.tex_rect_size.y);
				}
				//spr.invertTextureCoordinates();
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
			//Log("rendering particles");
		}
	}

	//mRenderer->setModelMatrix(mat4::identity);
	//KxDraw dr(((SystemKinesis2D*)mScene->mRegisteredSystems[0])->mPhysicsScene);
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void SystemRenderer::renderTilemap(Entity& entity)
{	
	mRenderer->setDepthTestEnabled(false);

	ComponentTilemap2D& tilemap = entity.getComponent<ComponentTilemap2D>();

	// Render a background
	RectangleShape BackgroundShape;
	BackgroundShape.setSize(tilemap.mLevelSize.x, tilemap.mLevelSize.y);
	BackgroundShape.setColors(Color::Blue, Color::Blue, Color::Blue, Color::Blue);
	BackgroundShape.setPosition(0.f, -tilemap.mLevelSize.y);
	mRenderer->draw(BackgroundShape);

	// Render all chunks for now

	mRenderer->setModelMatrix(mat4::translate(0, 0, 0));

	for(size_t j = 0; j < tilemap.mChunks.size(); ++j)
	{
		// Render each layer of each chunk
		for(size_t k = 0; k < tilemap.mChunks[j].mLayers.size(); ++k)
		{
			for(size_t index_set = 0; index_set < tilemap.mChunks[j].mLayers[k].mIndexSets.size(); ++index_set)
			{
				IndexArray& indexData = tilemap.mChunks[j].mLayers[k].mIndexSets[index_set];
				VertexArray& vertexData = tilemap.mChunks[j].mLayers[k].mVertexSets[index_set];

				if(indexData.size() > 0)
				{
					// Bind tileset 
					String tilesetResource = tilemap.mTilemapData.mTilesets[index_set].mPath;
					Path p(tilesetResource);
					tilesetResource = "textures/" + p.getFileName();
					//Log("RENDERING WITH TILESET %s", tilesetResource.c_str());
					glDisable( GL_MULTISAMPLE );
					mContentManager->getTexture(tilesetResource)->bind();
					//mRenderer->setDefaultTexture();

					mRenderer->enableVertexAttribArray(0);
					mRenderer->enableVertexAttribArray(1);
					mRenderer->enableVertexAttribArray(2);

					mRenderer->setVertexAttribPointer(0, 2, GL_FLOAT, false, vertexData.getVertexSize(), &vertexData.data[0] + vertexData.getAttributeOffset(0));
					mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, vertexData.getVertexSize(), &vertexData.data[0] + vertexData.getAttributeOffset(1));
					mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, vertexData.getVertexSize(), &vertexData.data[0] + vertexData.getAttributeOffset(2));

					glDrawElements(GL_TRIANGLES, indexData.indices.size(), GL_UNSIGNED_SHORT, &indexData.indices[0]);

					mRenderer->disableVertexAttribArray(0);
					mRenderer->disableVertexAttribArray(1);
					mRenderer->disableVertexAttribArray(2);
				}
			}
		}	
	}
}


};
NEPHILIM_NS_END