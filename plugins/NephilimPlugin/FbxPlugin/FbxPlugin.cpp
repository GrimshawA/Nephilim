#include "FbxPlugin.h"

#include <stdio.h>

#include <Nephilim/Foundation/Logging.h>

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

	FbxMesh* mesh = node->GetMesh();
	//mesh->

	for (auto i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		FbxVector4 cp = mesh->GetControlPointAt(i);
		//printf("cp %d  = %f %f %f %f\n", i, cp[0], cp[1], cp[2], cp[3]);
	}
}
