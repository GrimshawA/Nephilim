#include <Nephilim/Razer/SystemRenderer.h>
#include <Nephilim/Razer/World.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/Entity.inl>
#include <Nephilim/Razer/ComponentTilemap2D.h>
#include <Nephilim/Razer/ComponentTerrain.h>
#include <Nephilim/Razer/CCamera.h>
#include <Nephilim/Razer/CSprite.h>
#include <Nephilim/Razer/CTransform.h>
#include <Nephilim/Razer/CPointLight.h>
#include <Nephilim/Razer/ComponentParticleEmitter.h>
#include <Nephilim/Razer/ComponentModel.h>
#include <Nephilim/Razer/CMesh.h>
#include <Nephilim/Razer/ComponentVehicle.h>
#include <Nephilim/Razer/ComponentSkinnedModel.h>
#include <Nephilim/Razer/ComponentWater.h>
#include <Nephilim/Razer/ComponentWater2.h>
#include <Nephilim/Razer/SystemKinesis2D.h>

#include <Nephilim/NxMath.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/Path.h>
#include <Nephilim/CGL.h>

#include <Nephilim/Razer/PostEffectBloom.h>

NEPHILIM_NS_BEGIN
namespace rzr
{
	
SystemRenderer::SystemRenderer()
: RenderSystem()
, mRenderer(NULL)
, mContentManager(NULL)
, mTargetWidth(1900.f)
, mTargetHeight(1000.f)
{
	// add a test bloom effect
	mPostEffects.push_back(new PostEffectBloom);

	// init the render to texture
	mRenderTexture.create(mTargetWidth, mTargetHeight);
	if(mFramebuffer.create())
	{
		mFramebuffer.activate();
		mFramebuffer.attachTexture(mRenderTexture);

		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mTargetWidth, mTargetHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		Log(">>>>>>>>>>> Could not make render texture");
	}
	
}


/// This function will initialize the frame buffer and other things in order to produce a new frame out of the scene
void SystemRenderer::startFrame()
{
	// Bind render to texture
	mFramebuffer.activate();
	glViewport(0, 0, mTargetWidth, mTargetHeight);

	//mRenderer->setClearColor(Color::Blue);
	mRenderer->clearColorBuffer();
}

/// This function will basically truncate the output buffer and apply any post processing needed, generating the final composite
void SystemRenderer::endFrame()
{

	//mRenderer->setModelMatrix(mat4::identity);
	//	KxDraw dr(((SystemKinesis2D*)mScene->mRegisteredSystems[0])->mPhysicsScene);
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
	mRenderer->draw(finalComposite);

	mRenderer->setDefaultTarget();*/
}

/// All this function does is to render the current rendered scene frame to the backbuffer
void SystemRenderer::drawToBackBuffer()
{
	mRenderer->setDefaultTarget();
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
	mRenderer->draw(finalComposite);
}

void SystemRenderer::getActiveCamera(vec3& position, mat4& proj, mat4& view)
{
	// Find a camera
/*	for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		TEntity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentCamera>())
		{
			ComponentCamera& camera = ent.getComponent<ComponentCamera>();
			ComponentTransform& transform = ent.getComponent<ComponentTransform>();

			// Let's compute this camera transform
			camera.cameraTransform = mat4::identity;
			camera.cameraTransform = transform.rotation.toMatrix() * mat4::translate(-transform.position.x, -transform.position.y, -transform.position.z);

			if(camera.mOrtho)
			{
				mRenderer->setProjectionMatrix(mat4::ortho(-camera.size.x / 2.f, camera.size.x / 2.f, -camera.size.y / 2.f, camera.size.y / 2.f, camera.zNear, camera.zFar));
			}
			else
			{
				//mRenderer->setProjectionMatrix(mat4::perspective(camera.fieldOfView, 1700.f / 713.f, camera.zNear, camera.zFar));
				proj = mat4::perspective(camera.fieldOfView, 1700.f / 713.f, camera.zNear, camera.zFar);
			}

			//Log("FOUND CAMERA");

			view = camera.cameraTransform;

			position = transform.position;
			//cameraRotation = transform.rotation;
			//cameraForward  = transform.getForwardVector();
		}
	}*/
}

void SystemRenderer::update(const Time& deltaTime)
{
	// Update skinning animations
	/*for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentSkinnedModel>())
		{
			ComponentSkinnedModel& skinnedModel = ent.getComponent<ComponentSkinnedModel>();
			skinnedModel.update(deltaTime);
		}
	}*/
}

/// Render scene gets all scene render data and outputs it to the active target
void SystemRenderer::renderScene()
{

// 	RectangleShape c(FloatRect(100, 100, 1000, 1000), Color::Grass);
// 	mRenderer->draw(c);

	ComponentManager* meshComponentManager = mScene->getComponentManager<CMesh>();
	ComponentManager* pLightComponentManager = mScene->getComponentManager<CPointLight>();
	
	//Log("Num meshes: %d", meshComponentManager->getInstanceCount());

	// -- We have N meshes, we need to render all of them, but take into account the lights in the scene
	for (std::size_t i = 0; i < meshComponentManager->getInstanceCount(); ++i)
	{

	}

	renderAllSprites();

/*	mat4 viewMatrix;
	mat4 projectionMatrix;
	vec3 cameraPosition;
	Quaternion cameraRotation;
	vec3 cameraForward;

	// Find a camera
	for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
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
				mRenderer->setProjectionMatrix(mat4::ortho(-camera.size.x / 2.f, camera.size.x / 2.f, -camera.size.y / 2.f, camera.size.y / 2.f, camera.zNear, camera.zFar));
			}
			else
			{
				mRenderer->setProjectionMatrix(mat4::perspective(camera.fieldOfView, 1700.f / 713.f, camera.zNear, camera.zFar));
			}
			mRenderer->setViewMatrix(camera.cameraTransform);
			mRenderer->clearDepthBuffer();
			mRenderer->setDepthTestEnabled(false);
			mRenderer->clearColorBuffer();
			mRenderer->setBlendingEnabled(true);
			mRenderer->setBlendMode(Render::Blend::Alpha);

			//Log("FOUND CAMERA");

			viewMatrix = camera.cameraTransform;
			projectionMatrix = mRenderer->getProjectionMatrix();
			cameraPosition = transform.position;
			cameraRotation = transform.rotation;
			cameraForward  = transform.getForwardVector();
		}
	}

	// Render each entity
	for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentTilemap2D>())
		{
			renderTilemap(ent);
		}
		if(ent.hasComponent<ComponentSkinnedModel>())
		{
			ComponentSkinnedModel& skinnedModel = ent.getComponent<ComponentSkinnedModel>();
			ComponentTransform& transform = ent.getComponent<ComponentTransform>();
			mRenderer->setModelMatrix(transform.getMatrix() * skinnedModel.baseTransform);

			skinnedModel.render(mRenderer);
		}
		if(ent.hasComponent<ComponentVehicle>())
		{
			ComponentVehicle& v = ent.getComponent<ComponentVehicle>();

			// Draw the debug vehicle

			mRenderer->setDefaultTexture();

			btTransform trans;
			static_cast<btRigidBody*>(v.vehicle->m_carChassis)->getMotionState()->getWorldTransform(trans);
			btScalar mt[16];
			trans.getOpenGLMatrix(mt);
			mRenderer->setModelMatrix(mat4(mt) * v.testModelMatrix);
			//mRenderer->draw(v.vehicleChassis);

			// draw our test model
			v.testTexture.bind();
			mRenderer->draw(v.testModel);
			*/
			// Draw wheels
			/*v.vehicle->vehicle->getWheelInfo(0).m_worldTransform.getOpenGLMatrix(mt);
			mRenderer->setModelMatrix(mat4(mt));
			mRenderer->draw(v.vehicleWheel);
			v.vehicle->vehicle->getWheelInfo(1).m_worldTransform.getOpenGLMatrix(mt);
			mRenderer->setModelMatrix(mat4(mt));
			mRenderer->draw(v.vehicleWheel);
			v.vehicle->vehicle->getWheelInfo(2).m_worldTransform.getOpenGLMatrix(mt);
			mRenderer->setModelMatrix(mat4(mt));
			mRenderer->draw(v.vehicleWheel);
			v.vehicle->vehicle->getWheelInfo(3).m_worldTransform.getOpenGLMatrix(mt);
			mRenderer->setModelMatrix(mat4(mt));
			mRenderer->draw(v.vehicleWheel);*/
		/*}
		if(ent.hasComponent<ComponentTerrain>())
		{
			ent.getComponent<ComponentTerrain>().surfaceTex.bind();
			mRenderer->setDepthTestEnabled(true);
			mRenderer->setModelMatrix(ent.getComponent<ComponentTransform>().getMatrix());
			mRenderer->draw(ent.getComponent<ComponentTerrain>().geometry);
		}
		if(ent.hasComponent<ComponentModel>())
		{
			renderModel(ent);
		}
		if(ent.hasComponent<ComponentMesh>()) 
		{
			mRenderer->setDepthTestEnabled(true);
			renderMesh(ent);
		}
		if(ent.hasComponent<ComponentWater>()) 
		{
			mRenderer->setBlendingEnabled(false);
			//mRenderer->clearAllBuffers();
			mRenderer->setDefaultTexture();

			ComponentWater& waterBody = ent.getComponent<ComponentWater>();
			waterBody.viewMatrix = viewMatrix;
			waterBody.projMatrix = projectionMatrix;
			waterBody.cameraPosition = cameraPosition;
			vec3 eulerAngles = cameraRotation.eulerAngles();

			cameraRotation.normalize();

			vec3 z_vector(0.f, 0.f, -1.f);
			vec3 camera_vector = (cameraRotation.toMatrix() * vec4(z_vector, 0.f)).xyz();
			cameraForward.normalize();

			float x_angle = atan2(cameraForward.z, cameraForward.x);
			float y_angle = atan2(-cameraForward.z, cameraForward.y);
			//Log("x_angle %f", x_angle);

			//float camera_angle_x = atan2()

			waterBody.mCameraPhi = math::radianToDegree( x_angle);
			waterBody.mCameraTheta = math::radianToDegree( y_angle);


			if(!waterBody.ready)
				waterBody.init();

			waterBody.render2(mRenderer);

			mRenderer->setDefaultShader();
			mRenderer->setViewMatrix(mRenderer->getViewMatrix());
			mRenderer->setProjectionMatrix(mRenderer->getProjectionMatrix());
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
			spr.setScale(sprite.scale.x, -sprite.scale.y);
			spr.setColor(sprite.color);
			spr.setRotation(math::radianToDegree(sprite.rot));
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
			//Log("RENDERING");
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
			for(std::size_t j = 0; j < emitter.particles.size(); ++j)
			{
				mRenderer->draw(emitter.particles[j].mSprite);
			}
			mRenderer->setBlendMode(Render::Blend::Alpha);
			//Log("rendering particles");
		}
	}*/
}

void SystemRenderer::renderAllSprites()
{
	// Let's dirty draw all sprites
	ComponentManager* spriteComponentManager = mScene->getComponentManager<CSprite>();
	ComponentManager* transformComponentManager = mScene->getComponentManager<CTransform>();

	// Iterate all sprites we have spawned
	for (std::size_t i = 0; i < spriteComponentManager->getInstanceCount(); ++i)
	{
		// Get the i-th component in the manager
		CSprite* sprite = static_cast<CSprite*>(spriteComponentManager->getInstance(i));
		CTransform* transform = (CTransform*)transformComponentManager->getComponentFromEntity(spriteComponentManager->getInstanceEntity(i));
		

		mRenderer->setModelMatrix(transform->getMatrix() * mat4::scale(sprite->scale.x, sprite->scale.y, 1.f) * mat4::translate(-sprite->width / 2.f, -sprite->height / 2.f, 0.f));

		Texture* t = mContentManager->getTexture(sprite->tex);
		if (!t)
		{
			mContentManager->load(sprite->tex);
		}
		else
		{
			// draw
			RectangleShape c;
			c.setSize(sprite->width, sprite->height);
			c.setColor(sprite->color);
			c.setTexture(t);
			if (sprite->tex_rect_size.x > 0.f && sprite->tex_rect_size.y > 0.f)
			{
				c.setTextureRect(sprite->tex_rect_pos.x, sprite->tex_rect_pos.y, sprite->tex_rect_size.x, sprite->tex_rect_size.y);
				//c.setTextureRect(0.f, 0.f, 1000.f, 1000.f);
			}
			//c.invertTextureCoordinates();
			mRenderer->draw(c);
		}	
	}
}


void SystemRenderer::render()
{
	startFrame();
	renderScene();
	endFrame();
	drawToBackBuffer();
}

void SystemRenderer::renderModel(Entity& entity)
{
	
	/*CTransform& transform = entity.getComponent<CTransform>();

	float box_dims = 2.f;

	GeometryData box;
	box.addBox(box_dims, box_dims, box_dims);
	box.setAllColors(Color::White);


	mRenderer->setDepthTestEnabled(true);
	mRenderer->setModelMatrix(transform.getMatrix());
	mRenderer->setDefaultTexture();
	mRenderer->draw(box);

	box.setAllColors(Color::Black);
	box.m_primitive = Render::Primitive::LineLoop;
	glLineWidth(2.f);
	mRenderer->draw(box);

	//Log("Rendering the box");*/
}

void SystemRenderer::renderMesh(Entity& entity)
{
	/*ComponentMesh& mesh = entity.getComponent<ComponentMesh>();

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
	}*/
}

void SystemRenderer::renderTilemap(Entity& entity)
{	
	/*mRenderer->setDepthTestEnabled(false);

	ComponentTilemap2D& tilemap = entity.getComponent<ComponentTilemap2D>();

	// Render a background
	RectangleShape BackgroundShape;
	BackgroundShape.setSize(tilemap.mLevelSize.x, tilemap.mLevelSize.y);
	BackgroundShape.setColors(Color::Bittersweet, Color::Bittersweet, Color::Bittersweet, Color::Bittersweet);
	BackgroundShape.setPosition(0.f, -tilemap.mLevelSize.y);
	mRenderer->draw(BackgroundShape);

	//glDisable(GL_MULTISAMPLE);
	// Render all chunks for now

	mRenderer->setModelMatrix(mat4::translate(0, 0, 0));

	for(std::size_t j = 0; j < tilemap.mChunks.size(); ++j)
	{
		// Render each layer of each chunk
		for(std::size_t k = 0; k < tilemap.mChunks[j].mLayers.size(); ++k)
		{
			for(std::size_t index_set = 0; index_set < tilemap.mChunks[j].mLayers[k].mIndexSets.size(); ++index_set)
			{
				IndexArray& indexData = tilemap.mChunks[j].mLayers[k].mIndexSets[index_set];
				VertexArray& vertexData = tilemap.mChunks[j].mLayers[k].mVertexSets[index_set];

				if(indexData.size() > 0)
				{
					// Bind tileset 
					String tilesetResource = tilemap.mTilemapData.mTilesets[index_set].mPath;
					Path p(tilesetResource);
					tilesetResource = "/textures/" + p.getFileName();
					//Log("RENDERING WITH TILESET %s", tilesetResource.c_str());

					//Log("Rendering tilemap with texture %s", tilesetResource.c_str());
					
					Texture* tilesetTexture = mContentManager->getTexture(tilesetResource);
					if(tilesetTexture)
					{
						tilesetTexture->bind();
					}
					else
					{
						mRenderer->setDefaultTexture();
					}
		
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
	}*/
}


};
NEPHILIM_NS_END