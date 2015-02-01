#include <Nephilim/World/Systems/RenderSystemDefault.h>
#include <Nephilim/World/Systems/SystemKinesis2D.h>

#include <Nephilim/World/World.h>
#include <Nephilim/World/Level.h>
#include <Nephilim/World/Landscape.h>


#include <Nephilim/World/Entity.h>
#include <Nephilim/World/Entity.inl>
#include <Nephilim/World/CTransform.h>

#include <Nephilim/World/Components/ATilemapComponent.h>
#include <Nephilim/World/Components/ATerrainComponent.h>
#include <Nephilim/World/Components/ACameraComponent.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Components/AParticleEmitterComponent.h>
#include <Nephilim/World/Components/AStaticMeshComponent.h>
#include <Nephilim/World/Components/ATextComponent.h>
#include <Nephilim/World/Components/AInputComponent.h>
#include <Nephilim/World/Components/AProjectedWaterComponent.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Components/ASkeletalMeshComponent.h>

#include <Nephilim/Foundation/Math.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Path.h>

#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Graphics/GL/GLTextureCube.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>
#include <Nephilim/Graphics/Shader.h>
#include <Nephilim/Graphics/Text.h>

#include <Nephilim/World/PostEffectBloom.h>

NEPHILIM_NS_BEGIN
	
RenderSystemDefault::RenderSystemDefault()
: RenderSystem()
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
void RenderSystemDefault::startFrame()
{
	
}

/// This function will basically truncate the output buffer and apply any post processing needed, generating the final composite
void RenderSystemDefault::endFrame()
{

}

/// All this function does is to render the current rendered scene frame to the backbuffer
void RenderSystemDefault::drawToBackBuffer()
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

void RenderSystemDefault::getActiveCamera(vec3& position, mat4& proj, mat4& view)
{

}

void RenderSystemDefault::update(const Time& deltaTime)
{

}

Texture* skyBoxTexture;

TextureCube* cubeMap;

void DrawGeometry(GraphicsDevice* graphics, const Geometry& geom)
{
	graphics->enableVertexAttribArray(0);
	graphics->enableVertexAttribArray(1);
	graphics->enableVertexAttribArray(2);
	graphics->setDefaultTexture();

	if (skyBoxTexture)
		skyBoxTexture->bind();

	graphics->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &geom._positions[0]);
	graphics->setVertexAttribPointer(1, 4, GL_FLOAT, false, 0, &geom._colors[0]);
	graphics->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &geom._texcoord[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &geom._faces[0]);

	graphics->disableVertexAttribArray(0);
	graphics->disableVertexAttribArray(1);
	graphics->disableVertexAttribArray(2);
}



/// Render a sky box into the map
void RenderSystemDefault::renderSkyBox()
{
	static bool loaded = false;
	if (!loaded)
	{
		skyBoxTexture = new Texture();
		if (skyBoxTexture->loadFromFile("Textures/skyboxsun25degtest.png"))
		{
			Log("SKYBOX IS LOADED");
		}

		cubeMap = new GLTextureCube();
		cubeMap->test();

		loaded = true;
	}

	Log("Rendering BOX");

	Geometry top_plane = Geometry::GeneratePlane(Vector3D(), Vector3D(), Vector2D());
	
	mat4 proj = mRenderer->getProjectionMatrix();
	mat4 view = mRenderer->getViewMatrix();

	// The sky box doesn't respond to camera transforms (we're at 0,0,0 all the time and the skybox is around us)
	mRenderer->setViewMatrix(camRot);

	top_plane._texcoord[0] = vec2(0.5f, 0.f);
	top_plane._texcoord[1] = vec2(0.5f, 0.25f);
	top_plane._texcoord[2] = vec2(0.25f, 0.25f);
	top_plane._texcoord[3] = vec2(0.25f, 0.f);


	DrawGeometry(mRenderer, top_plane);

	mRenderer->setProjectionMatrix(proj);
	mRenderer->setViewMatrix(view);
}

/// Render scene gets all scene render data and outputs it to the active target
void RenderSystemDefault::renderScene()
{
	//renderSkyBox();

	mRenderer->clearDepthBuffer();

	// Draw level terrains if applicable
	for (std::size_t i = 0; i < mWorld->levels.size(); ++i)
	{
		Level* level = mWorld->getLevel(i);

		for (std::size_t j = 0; j < level->landscapes.size(); ++j)
		{
			level->landscapes[j]->terrain.surfaceTex.bind();

			mRenderer->setDepthTestEnabled(true);
			mRenderer->setModelMatrix(level->landscapes[j]->rootTransform.getMatrix());
			mRenderer->draw(level->landscapes[j]->terrain.geometry);
		}
	}


	ComponentManager* meshComponentManager = mWorld->getComponentManager<AStaticMeshComponent>();
	ComponentManager* transformComponentManager = mWorld->getComponentManager<CTransform>();
	//ComponentManager* pLightComponentManager = mScene->getComponentManager<CPointLight>();
	
	//Log("Num meshes: %d", meshComponentManager->getInstanceCount());

	// -- We have N meshes, we need to render all of them, but take into account the lights in the scene
	for (std::size_t i = 0; i < meshComponentManager->size(); ++i)
	{
		CTransform* transform = (CTransform*)transformComponentManager->getComponentFromEntity(meshComponentManager->getInstanceEntity(i));
		AStaticMeshComponent* mesh = (AStaticMeshComponent*)meshComponentManager->getInstance(i);

		if (mesh->materials.size() > 0)
		{
			for (std::size_t i = 0; i < mesh->materials.size(); ++i)
			{
				Texture* diff_texture = mContentManager->getTexture(mesh->materials[i].diffuse);
				if (diff_texture)
					diff_texture->bind();
				else
				{
					mContentManager->load(mesh->materials[i].diffuse);
					Texture* diff_texture = mContentManager->getTexture(mesh->materials[i].diffuse);
					diff_texture->setRepeated(true);
				}
			}			

			mRenderer->setModelMatrix(transform->getMatrix());
			mRenderer->draw(mesh->staticMesh.ptr->geom);
		}
		else
		{
			mRenderer->setDefaultTexture();
			mRenderer->setModelMatrix(transform->getMatrix());
			mRenderer->draw(mesh->staticMesh.ptr->geom);
		}		
	}

	renderAllSprites();

	// Don't have actors caching their components by type, need to go get them directly in the actor
	for (std::size_t i = 0; i < mWorld->actors.size(); ++i)
	{
		Actor* actor = mWorld->actors[i];
		for (std::size_t j = 0; j < actor->components.size(); ++j)
		{
			ASpriteComponent* spriteComponent = dynamic_cast<ASpriteComponent*>(actor->components[j]);
			if (spriteComponent)
			{
				//renderSprite(&spriteComponent->t, spriteComponent);
			}

			ATextComponent* textComponent = dynamic_cast<ATextComponent*>(actor->components[j]);
			if (textComponent)
			{
				Text t;
				t.setString(textComponent->text);
				t.setFont(mContentManager->font);
				t.setCharacterSize(15);
				t.useOwnTransform = false;
				mRenderer->setModelMatrix(textComponent->t.getMatrix() * mat4::scale(1.f, -1.f, 1.f));
				mRenderer->draw(t);
			}

			AParticleEmitterComponent* particleEmitter = dynamic_cast<AParticleEmitterComponent*>(actor->components[j]);
			if (particleEmitter)
			{
				for (auto k = 0; k < particleEmitter->particles.size(); ++k)
				{
					mat4 model = mat4::translate(particleEmitter->particles[k].position);

					RectangleShape c(FloatRect(0.f, 0.f, 30.f, 30.f), Color::Orange);
					c.useOwnTransform = false;
					mRenderer->setModelMatrix(model);
					mRenderer->draw(c);
				}
			}

			AStaticMeshComponent* staticMeshComponent = dynamic_cast<AStaticMeshComponent*>(actor->components[j]);
			if (staticMeshComponent)
			{
				mat4 modelPose = staticMeshComponent->absoluteTransform;
				AStaticMeshComponent* mesh = staticMeshComponent;

				if (mesh->materials.size() > 0)
				{
					for (std::size_t i = 0; i < mesh->materials.size(); ++i)
					{
						Texture* diff_texture = mContentManager->getTexture(mesh->materials[i].diffuse);
						if (diff_texture)
						{
							diff_texture->bind();
							//Log("Binding texture %s", mesh->materials[i].diffuse.c_str());
						}
						else
						{
							if (!mContentManager->load(mesh->materials[i].diffuse))
							{
								Log("Failed to load a texture");
							}
							Texture* diff_texture = mContentManager->getTexture(mesh->materials[i].diffuse);
							diff_texture->setRepeated(true);
						}
					}

					// let's draw the actual thing		
					mRenderer->setModelMatrix(modelPose);
					mRenderer->draw(mesh->staticMesh->_vertexArray, mesh->staticMesh->_indexArray);

					mRenderer->setModelMatrix(modelPose);
					mRenderer->draw(mesh->staticMesh.ptr->geom);			
				}
				else
				{
					mRenderer->setDefaultTexture();
					mRenderer->setModelMatrix(modelPose);
					mRenderer->draw(mesh->staticMesh.ptr->geom);

					// let's draw the actual thing
					mRenderer->setDefaultTexture();
					mRenderer->setModelMatrix(modelPose);
					mRenderer->draw(mesh->staticMesh->_vertexArray, mesh->staticMesh->_indexArray);
				}
			}

			// Check for skeletal meshes
			ASkeletalMeshComponent* skeletalMeshComponent = dynamic_cast<ASkeletalMeshComponent*>(actor->components[j]);
			if (skeletalMeshComponent)
			{
				// Prepare the model matrices
				mRenderer->setModelMatrix(actor->getActorTransform().getMatrix() * mat4::rotatey(math::pi));
			
				// Now activate the right shader and uniforms
				Shader s;
				s.shaderImpl = &skeletalMeshComponent->rigShader;
				mRenderer->setShader(s);
				mRenderer->setModelMatrix(mRenderer->getModelMatrix());
				mRenderer->setProjectionMatrix(mRenderer->getProjectionMatrix());
				mRenderer->setViewMatrix(mRenderer->getViewMatrix());
				
				for (auto& m : skeletalMeshComponent->boneTransforms)
				{
					//m = mat4::identity;
				}

				int location = glGetUniformLocation(skeletalMeshComponent->rigShader.m_id, "u_BoneTransform");
				glUniformMatrix4fv(location, 128, false, reinterpret_cast<float*>(&skeletalMeshComponent->boneTransforms[0]));

				//skeletalMeshComponent->model->render(mRenderer);
				
				if (skeletalMeshComponent->skeletalMeshAsset)
				{
					skeletalMeshComponent->myT.bind();
					//mRenderer->draw(skeletalMeshComponent->model->champion);

					
					mRenderer->enableVertexAttribArray(0);
					mRenderer->enableVertexAttribArray(1);
					mRenderer->enableVertexAttribArray(2);
					mRenderer->enableVertexAttribArray(3);
					mRenderer->enableVertexAttribArray(4);
					mRenderer->enableVertexAttribArray(5);

					// positions
					mRenderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), skeletalMeshComponent->skeletalMeshAsset->_vertexArray.data());
					
					mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), &skeletalMeshComponent->skeletalMeshAsset->_vertexArray._data[0] + skeletalMeshComponent->skeletalMeshAsset->_vertexArray.getAttributeOffset(1));
					
					// 2 = uv
					mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), &skeletalMeshComponent->skeletalMeshAsset->_vertexArray._data[0] + skeletalMeshComponent->skeletalMeshAsset->_vertexArray.getAttributeOffset(2));
				
					// 3 = n
					mRenderer->setVertexAttribPointer(3, 3, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), &skeletalMeshComponent->skeletalMeshAsset->_vertexArray._data[0] + skeletalMeshComponent->skeletalMeshAsset->_vertexArray.getAttributeOffset(3));
					mRenderer->setVertexAttribPointer(4, 4, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), &skeletalMeshComponent->skeletalMeshAsset->_vertexArray._data[0] + skeletalMeshComponent->skeletalMeshAsset->_vertexArray.getAttributeOffset(4));
					mRenderer->setVertexAttribPointer(5, 4, GL_FLOAT, false, skeletalMeshComponent->skeletalMeshAsset->_vertexArray.stride(), &skeletalMeshComponent->skeletalMeshAsset->_vertexArray._data[0] + skeletalMeshComponent->skeletalMeshAsset->_vertexArray.getAttributeOffset(5));

					glDrawElements(GL_TRIANGLES, skeletalMeshComponent->skeletalMeshAsset->_indexArray.size(), GL_UNSIGNED_SHORT, skeletalMeshComponent->skeletalMeshAsset->_indexArray.data());

					mRenderer->disableVertexAttribArray(0);
					mRenderer->disableVertexAttribArray(1);
					mRenderer->disableVertexAttribArray(2);
					mRenderer->disableVertexAttribArray(3);
					mRenderer->disableVertexAttribArray(4);
					mRenderer->disableVertexAttribArray(5);

				}

				mRenderer->setDefaultShader();
			}
		}
	}
}

void RenderSystemDefault::renderSprite(CTransform* transform, ASpriteComponent* sprite)
{
	//Log("ACTOR SPRITE");

	mRenderer->setModelMatrix(transform->getMatrix() * mat4::scale(sprite->scale.x, sprite->scale.y, 1.f) * mat4::translate(-sprite->width / 2.f, -sprite->height / 2.f, 0.f));

	Texture* t = mContentManager->getTexture(sprite->tex);
	if (!t)
	{
		mContentManager->load(sprite->tex);
	}
	else
	{
		VertexArray va;
		va.addAttribute(sizeof(float), 2, VertexFormat::Position);
		va.addAttribute(sizeof(float), 4, VertexFormat::Color);
		va.addAttribute(sizeof(float), 2, VertexFormat::TexCoord);
		va.allocateData(6);

		struct vertex_f
		{
			vec2 p;
			vec4 c;
			vec2 uv;
		};

		//			Log("Rendering sprite %f %f", sprite->width, sprite->height);


		vertex_f* va_raw = reinterpret_cast<vertex_f*>(&va._data[0]);

		va_raw[0].p = vec2(sprite->width, 0.f);
		va_raw[1].p = vec2(sprite->width, sprite->height);
		va_raw[2].p = vec2(0.f, sprite->height);

		va_raw[3].p = vec2(sprite->width, 0.f);
		va_raw[4].p = vec2(0.f, sprite->height);
		va_raw[5].p = vec2(0.f, 0.f);

		va_raw[0].uv = vec2(1.f, 0.f);
		va_raw[1].uv = vec2(1.f, 1.f);
		va_raw[2].uv = vec2(0.f, 1.f);

		va_raw[3].uv = vec2(1.f, 0.f);
		va_raw[4].uv = vec2(0.f, 1.f);
		va_raw[5].uv = vec2(0.f, 0.f);

		if (sprite->tex_rect_size.x > 0.f && sprite->tex_rect_size.y > 0.f)
		{
			float x1 = sprite->tex_rect_pos.x / t->getSize().x;
			float x2 = x1 + sprite->tex_rect_size.x / t->getSize().x;

			float y1 = sprite->tex_rect_pos.y / t->getSize().y;
			float y2 = y1 + sprite->tex_rect_size.y / t->getSize().y;

			va_raw[0].uv = vec2(x2, y1);
			va_raw[1].uv = vec2(x2, y2);
			va_raw[2].uv = vec2(x1, y2);

			va_raw[3].uv = vec2(x2, y1);
			va_raw[4].uv = vec2(x1, y2);
			va_raw[5].uv = vec2(x1, y1);
		}

		va_raw[0].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);
		va_raw[1].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);
		va_raw[2].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);
		va_raw[3].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);
		va_raw[4].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);
		va_raw[5].c = vec4(float(sprite->color.r) / 255.f, float(sprite->color.g) / 255.f, float(sprite->color.b) / 255.f, float(sprite->color.a) / 255.f);

		mRenderer->enableVertexAttribArray(0);
		mRenderer->enableVertexAttribArray(1);
		mRenderer->enableVertexAttribArray(2);

		mRenderer->setVertexAttribPointer(0, 2, GL_FLOAT, false, va.getVertexSize(), &va._data[0] + va.getAttributeOffset(0));
		mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, va.getVertexSize(), &va._data[0] + va.getAttributeOffset(1));
		mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, va.getVertexSize(), &va._data[0] + va.getAttributeOffset(2));

		mRenderer->setModelMatrix(transform->getMatrix() * mat4::scale(sprite->scale.x, sprite->scale.y, 1.f) * mat4::translate(-sprite->width / 2.f, -sprite->height / 2.f, 0.f));

		t->bind();
		mRenderer->drawArrays(Render::Primitive::Triangles, 0, 6);

		mRenderer->disableVertexAttribArray(0);
		mRenderer->disableVertexAttribArray(1);
		mRenderer->disableVertexAttribArray(2);

		mRenderer->setModelMatrix(mat4::identity);
		mRenderer->setDefaultTexture();

		//Log("RENDERING SPRITE");

	}
}


void RenderSystemDefault::renderAllSprites()
{
	// Let's dirty draw all sprites
	ComponentManager* spriteComponentManager = mWorld->getComponentManager<ASpriteComponent>();
	ComponentManager* transformComponentManager = mWorld->getComponentManager<CTransform>();

	// Iterate all sprites we have spawned
	for (std::size_t i = 0; i < spriteComponentManager->size(); ++i)
	{
		// Get the i-th component in the manager
		ASpriteComponent* sprite = static_cast<ASpriteComponent*>(spriteComponentManager->getInstance(i));
		CTransform* transform = (CTransform*)transformComponentManager->getComponentFromEntity(spriteComponentManager->getInstanceEntity(i));
		
		renderSprite(transform, sprite);
	}
}


void RenderSystemDefault::render()
{
	// Let's activate the proper camera
	if (mWorld->_viewports.empty())
		return;

	mRenderer->setProjectionMatrix(mWorld->_viewports[0]._camera.lens.getProjection());
	mRenderer->setViewMatrix(mWorld->_viewports[0]._camera.transform.getMatrix().inverse());

	startFrame();
	renderScene();
}

void RenderSystemDefault::renderModel(Entity& entity)
{
}

void RenderSystemDefault::renderMesh(Entity& entity)
{
}

void RenderSystemDefault::renderTilemap(Entity& entity)
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


NEPHILIM_NS_END