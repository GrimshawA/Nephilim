#ifndef FileWriter_h__
#define FileWriter_h__

#include "SKLLoader.h"
#include "SKNLoader.h"

class LOLImporterX
{
public:


	/// 
	static bool WriteGeometryFile(const String& skn_file, const String& skl_file, const String& filename)
	{
		GeometryData geom;
		SKNLoader SKN;
		SKN.Load(geom, skn_file);

		SkeletonSKL skel;
		skel.Load(skl_file);

		for (int i = 0; i < SKN.boneIDs.size(); ++i)
		{
			SKN.boneIDs[i].x = skel.boneIndexToActualBone[SKN.boneIDs[i].x];
			SKN.boneIDs[i].y = skel.boneIndexToActualBone[SKN.boneIDs[i].y];
			SKN.boneIDs[i].z = skel.boneIndexToActualBone[SKN.boneIDs[i].z];
			SKN.boneIDs[i].w = skel.boneIndexToActualBone[SKN.boneIDs[i].w];

			// I GUESS I NEED TO SHIFT WEIGHTS TOO
		}

		return SKN.write_ngf(filename, &skel);
	}
};

#endif // FileWriter_h__
