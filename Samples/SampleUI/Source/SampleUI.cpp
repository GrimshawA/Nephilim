#include "SampleUI.h"
#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/MMath.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Profiler.h>
#include <Nephilim/Text.h>
#include <Nephilim/AssimpConverter.h>
#include <Nephilim/Engine.h>
//#include <Nephilim/ASXEngine.h>
#include <Nephilim/File.h>

#include <iostream>
using namespace std;

GeometryData ironman;
GeometryData ironman2;

Texture ironmantexture;

Text text;
Font *font;

#include <assimp/scene.h>

AssimpImport import; /// Init
float elapsedTime = 0.f;
float localElapsedTime = 0.f;
int currentOffset = 0;

mat4 getCurrentTransform()
{
	const aiScene* scene = import.getScene();
	aiAnimation* animation = scene->mAnimations[0];
	//Log("Animation 1 channel count: %d",animation->mNumMeshChannels);
	aiNodeAnim* nodeanim = animation->mChannels[0];
	double finalTime = 0.f;
	for(int i = 0; i < nodeanim->mNumPositionKeys; ++i)
	{
		//Log("Position key:%f %f %f %f",nodeanim->mPositionKeys[i].mTime, nodeanim->mPositionKeys[i].mValue.x, nodeanim->mPositionKeys[i].mValue.y, nodeanim->mPositionKeys[i].mValue.z);
	
		//Log("Times: %f", nodeanim->mPositionKeys[i].mTime);
		//cout << "time : "<<nodeanim->mPositionKeys[i].mTime<<endl;
		finalTime += nodeanim->mPositionKeys[i].mTime;

		//Log("%f > %f", elapsedTime , finalTime);
		if( i == currentOffset)
		{
			if(elapsedTime >= finalTime)
			{
				currentOffset++;
				localElapsedTime = 0.f;
				Log("next keyframe");
			}
			// return interpolation between both positions
			vec3 thisPosition = vec3(nodeanim->mPositionKeys[i].mValue.x, nodeanim->mPositionKeys[i].mValue.y, nodeanim->mPositionKeys[i].mValue.z);
			vec3 nextPosition = vec3(nodeanim->mPositionKeys[i+1].mValue.x, nodeanim->mPositionKeys[i+1].mValue.y, nodeanim->mPositionKeys[i+1].mValue.z);
			vec3 interpolated = thisPosition + (nextPosition - thisPosition) * localElapsedTime;
			return mat4::translate(interpolated.x, interpolated.y, interpolated.z);
		}
		
	}
	return mat4();
}

void SampleUI::onCreate()
{	
	//ironmantexture.loadFromFile("maps/mk7.png");
	//ironmantexture.setRepeated(true);

	import.load("blender.DAE"); /// Load

	AssimpGeometry converter(ironman, import);
	ironman.setAllColors(Color::White);

	const aiScene* scene = import.getScene();
	if(scene->HasAnimations())
	{
		Log("Num Bones: %d", scene->mMeshes[0]->mNumBones);
		Log("Animations found: %d", scene->mNumAnimations);
		aiAnimation* animation = scene->mAnimations[0];
		Log("Channel count: %d", animation->mNumChannels);
		Log("Name: %s", animation->mName.C_Str());
		Log("Duration: %f", animation->mDuration);
		Log("Mesh Channels: %d", animation->mNumMeshChannels);
		Log("Ticks: %f", animation->mTicksPerSecond);
		aiNodeAnim* nodeanim = animation->mChannels[0];
		Log("Animation rotation keys: %d", nodeanim->mNumRotationKeys);
		Log("Animation scaling keys: %d", nodeanim->mNumScalingKeys);

		for(int i = 0; i < nodeanim->mNumPositionKeys; ++i)
		{
			Log("Position key: %f %f %f", nodeanim->mPositionKeys[i].mValue.x, nodeanim->mPositionKeys[i].mValue.y, nodeanim->mPositionKeys[i].mValue.z);
		}

	}
	else Log("No animations found.");
	

//	ironman.saveToFile("torusknot.ngx");

	//ironman2.loadFromFile("ironman.ngx");
}

void SampleUI::onEvent(Event &event)
{
    
}


void SampleUI::onUpdate(Time time)
{ 
	elapsedTime += time.asSeconds(); // update slowly
	localElapsedTime += time.asSeconds() ; // update slowly
//	Log("time: %f", elapsedTime);
}



void SampleUI::onRender()
{
	// Ensure default shader
	getRenderer()->setDefaultShader();

	getRenderer()->setDepthTestEnabled(true);
	getRenderer()->clearAllBuffers();
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(mat4::perspective(45, 1024.f / 768.f, 1.f, 1000.f));
	getRenderer()->setViewMatrix(mat4::lookAt(vec3(1,20,20), vec3(0,1,0), vec3(0,1,0)));
	getRenderer()->setDefaultTexture();
	
	static float angle = 0; angle+=0.005;
	//getRenderer()->setModelMatrix(mat4::rotatey(angle));

	getRenderer()->setModelMatrix(getCurrentTransform());
	try
	{
		getRenderer()->setDefaultTexture();
		getRenderer()->enableVertexAttribArray(0);
		getRenderer()->enableVertexAttribArray(1);
		//getRenderer()->enableVertexAttribArray(2);
		getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &ironman.m_vertices[0]);
			getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &ironman.m_colors[0]);
		//	getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &ironman.m_texCoords[0]);
		getRenderer()->drawArrays(Render::Primitive::Triangles, 0, ironman.m_vertices.size());
		getRenderer()->disableVertexAttribArray(0);
	}
	catch (...)
	{
		Log("Error happened in draw");
	}



	//getRenderer()->disableVertexAttribArray(1);
	//getRenderer()->disableVertexAttribArray(2);

	

	//ironmantexture.bind();
	/*getRenderer()->setModelMatrix(mat4::rotatey(angle) * mat4::translate(1, 0, 0));
	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->enableVertexAttribArray(1);
	getRenderer()->enableVertexAttribArray(2);
	getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &ironman2.m_vertices[0]);
	getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &ironman2.m_colors[0]);
	getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &ironman2.m_texCoords[0]);
	getRenderer()->drawArrays(Render::Primitive::Triangles, 0, ironman2.m_vertices.size());*/
	
}
