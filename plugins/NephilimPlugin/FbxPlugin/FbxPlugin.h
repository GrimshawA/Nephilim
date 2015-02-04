#ifndef FbxPlugin_h__
#define FbxPlugin_h__

#include <Nephilim/Foundation/Extension.h>
#include <Nephilim/Foundation/ExtensionImporter.h>
using namespace nx;

#include <fbxsdk.h>

/*
	\class NephilimFbxPlugin
	\brief Provides all import and export functionality of the FBX SDK to nephilim
*/
class NephilimFbxPlugin : public ExtensionImporter
{
public:

	/// Convert a source file into native formats
	virtual bool importToNative(const String& filename);

public:

	/// Processing a node means handling it and its children recursively
	void ProcessNode(FbxNode* node);
	
	/// Process a mesh node
	void ProcessMesh(FbxNode* node);

};

#endif // FbxPlugin_h__
