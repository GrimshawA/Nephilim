#include "FbxPlugin.h"

#include <stdio.h>
#include <map>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Graphics/Geometry.h>
#include <Nephilim/Graphics/GeomFmt.h>

/// FbxNode with a mesh and its engine representation
std::map<FbxNode*, GeometryObject> _gMeshes;


/// Convert a source file into native formats
bool NephilimFbxPlugin::importToNative(const String& filename)
{
	FbxManager* sdkManager = FbxManager::Create();

	FbxIOSettings *ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ios);

	FbxImporter* lImporter = FbxImporter::Create(sdkManager, "");

	if (!lImporter->Initialize(filename.c_str(), -1, sdkManager->GetIOSettings()))
	{
		printf("Hell breaks loose\n");
		return false;
	}
	
	// Now let's populate our scene
	FbxScene* lScene = FbxScene::Create(sdkManager, "scene");



	lImporter->Import(lScene);
	lImporter->Destroy();

	FbxAxisSystem directXAxisSys(FbxAxisSystem::EUpVector::eYAxis,
		FbxAxisSystem::EFrontVector::eParityEven,
		FbxAxisSystem::eRightHanded);
	directXAxisSys.ConvertScene(lScene);

	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		ProcessNode(lRootNode);
	}
	
	sdkManager->Destroy();

	return true;
}

void NephilimFbxPlugin::ProcessNode(FbxNode* node)
{
	// Extract node stuff
	for (auto i = 0; i < node->GetNodeAttributeCount(); ++i)
	{
		FbxNodeAttribute* nodeAttribute = node->GetNodeAttributeByIndex(i);
		switch (nodeAttribute->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:
			ProcessMesh(node);
			break;
		}
	}


	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* child = node->GetChild(i);
		Log("Child %s", child->GetName());
		ProcessNode(child);
	}
}

/// Process a mesh node
void NephilimFbxPlugin::ProcessMesh(FbxNode* node)
{
	printf("Found here a mesh\n");

	/// The fbx mesh for the data
	FbxMesh* mesh = node->GetMesh();

	/// Our engine mesh for the conversion
	GeometryObject& obj = _gMeshes[node];



	for (auto i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		FbxVector4 cp = mesh->GetControlPointAt(i);
		//printf("cp %d  = %f %f %f %f\n", i, cp[0], cp[1], cp[2], cp[3]);
	}

	/// Iterate faces
	for (auto i = 0; i < mesh->GetPolygonCount(); ++i)
	{
		int face0 = mesh->GetPolygonVertex(i, 0);
		int face1 = mesh->GetPolygonVertex(i, 1);
		int face2 = mesh->GetPolygonVertex(i, 2);

		FbxVector4 cp0 = mesh->GetControlPointAt(face0);
		FbxVector4 cp1 = mesh->GetControlPointAt(face1);
		FbxVector4 cp2 = mesh->GetControlPointAt(face2);

		obj.vertices.push_back(Vector3D(cp0[0], cp0[1], cp0[2]));
		obj.vertices.push_back(Vector3D(cp1[0], cp1[1], cp1[2]));
		obj.vertices.push_back(Vector3D(cp2[0], cp2[1], cp2[2]));

		// Normals
		FbxVector4 normal0;
		FbxVector4 normal1;
		FbxVector4 normal2;
		mesh->GetPolygonVertexNormal(i, 0, normal0);
		mesh->GetPolygonVertexNormal(i, 1, normal1);
		mesh->GetPolygonVertexNormal(i, 2, normal2);
		obj.normals.push_back(Vector3D(normal0[0], normal0[1], normal0[2]));
		obj.normals.push_back(Vector3D(normal1[0], normal1[1], normal1[2]));
		obj.normals.push_back(Vector3D(normal2[0], normal2[1], normal2[2]));

		// Texcoord0
		FbxStringList SetUVNames;
		mesh->GetUVSetNames(SetUVNames);
		if (SetUVNames.GetCount() > 0)
		{
			Log("UV SETS: %d", SetUVNames.GetCount());

			FbxString set_uv0 = SetUVNames.GetStringAt(0);

			FbxVector2 uv0_0;
			FbxVector2 uv0_1;
			FbxVector2 uv0_2;
			bool mapped0;

			mesh->GetPolygonVertexUV(i, 0, set_uv0, uv0_0, mapped0);
			mesh->GetPolygonVertexUV(i, 1, set_uv0, uv0_1, mapped0);
			mesh->GetPolygonVertexUV(i, 2, set_uv0, uv0_2, mapped0);

			obj.texcoords0.push_back(Vector2D(uv0_0[0], uv0_0[1]));
			obj.texcoords0.push_back(Vector2D(uv0_1[0], uv0_1[1]));
			obj.texcoords0.push_back(Vector2D(uv0_2[0], uv0_2[1]));

			//Log("uv: %f %f", obj.texcoords0[obj.texcoords0.size() - 1].x, obj.texcoords0[obj.texcoords0.size() - 1].y);
		}
	}

	obj.saveToFile("Out.ngf");
}
