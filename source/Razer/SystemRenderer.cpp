#include <Nephilim/Razer/SystemRenderer.h>
#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/ComponentTilemap2D.h>
#include <Nephilim/Razer/ComponentTerrain.h>
#include <Nephilim/Razer/ComponentCamera.h>
#include <Nephilim/Razer/ComponentMesh.h>
#include <Nephilim/Razer/SystemKinesis2D.h>

#include <Nephilim/Logger.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/CGL.h>

NEPHILIM_NS_BEGIN
namespace rzr{
	
SystemRenderer::SystemRenderer()
: System()
{

}

void SystemRenderer::render()
{
	// Find a camera
	for(size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity ent = mScene->getEntityByIndex(i);
		if(ent.hasComponent<ComponentCamera>())
		{
			ComponentCamera& camera = ent.getComponent<ComponentCamera>();

			mRenderer->setProjectionMatrix(mat4::perspective(90.f, 1000.f / 500.f, 1.f, 1000.f));
			mRenderer->setViewMatrix(mat4::lookAt(vec3(camera.x, camera.y, camera.z), vec3(camera.center_x, camera.center_y, camera.center_z) , camera.up));
			mRenderer->clearDepthBuffer();
			mRenderer->setDepthTestEnabled(true);
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
		else if(ent.hasComponent<ComponentTerrain>())
		{
			ent.getComponent<ComponentTerrain>().surfaceTex.bind();
			mRenderer->draw(ent.getComponent<ComponentTerrain>().geometry);
		}
		else if(ent.hasComponent<ComponentMesh>())
		{
			renderMesh(ent);
		}
	}

	KxDraw dr(((SystemKinesis2D*)mScene->mRegisteredSystems[0])->mScene);
	mRenderer->draw(dr);
}

void SystemRenderer::renderMesh(Entity& entity)
{
	ComponentMesh& mesh = entity.getComponent<ComponentMesh>();

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

		mRenderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(0));
		mRenderer->setVertexAttribPointer(1, 4, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(1));
		mRenderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, mesh.mVertexArray.getVertexSize(), &mesh.mVertexArray.data[0] + mesh.mVertexArray.getAttributeOffset(2));

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