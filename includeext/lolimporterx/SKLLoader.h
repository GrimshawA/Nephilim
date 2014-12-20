#ifndef SKLLoader_h__
#define SKLLoader_h__

#include <Nephilim/Strings.h>
#include <Nephilim/File.h>
#include <Nephilim/DataStream.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Math/Quaternion.h>
using namespace nx;

#include <vector>

class BoneSKL
{
public:
	String name;
	Int32 id;
	Int32 parentID;
	float scale;

	//3x4 matrix..
	float orientation[12];
	vec3 position;

	mat4 inverseBindPose;
	mat4 bindPose;
};

class SkeletonSKL
{
public:

	String id;
	Uint32 version;
	Uint32 designerID;
	Uint32 numBones;
	std::vector<BoneSKL> bones;

	std::vector<int> boneIndexToActualBone;

	void Load(const String& filename)
	{
		File myFile(filename, IODevice::BinaryRead);

		if(!myFile)
			return;

		DataStream dstream(myFile);

		for(int i = 0; i < 8; i++)
			id += dstream.readChar();

		dstream >> version;

		Log("Loading SKL: %s, version %d", id.c_str(), version);

		// Loading what I need only..
		if(version == 1 || version == 2)
		{
			dstream >> designerID;
			dstream >> numBones;
			bones.resize(numBones);

			Log("Num Bones: %d", numBones);
			for(int i = 0; i < numBones; ++i)
			{
				for(int j = 0; j < 32; j++)
					bones[i].name += dstream.readChar();

				bones[i].id = i;
				dstream >> bones[i].parentID;
				dstream >> bones[i].scale;

				for(int j = 0; j < 12 ; ++j)
				{
					dstream >> bones[i].orientation[j];
				}

				bones[i].position.x = bones[i].orientation[3];
				bones[i].position.y = bones[i].orientation[7];
				bones[i].position.z = bones[i].orientation[11];

				// lets get a bind pose matrix 4x4, no translation
				float bindPoseRowMajor[16];

				// column 1
				bindPoseRowMajor[0] = bones[i].orientation[0];
				bindPoseRowMajor[1] = bones[i].orientation[4];
				bindPoseRowMajor[2] = bones[i].orientation[8];
				bindPoseRowMajor[3] = 0;

				// column 2
				bindPoseRowMajor[4] = bones[i].orientation[1];
				bindPoseRowMajor[5] = bones[i].orientation[5];
				bindPoseRowMajor[6] = bones[i].orientation[9];
				bindPoseRowMajor[7] = 0;

				// column 3
				bindPoseRowMajor[8] = bones[i].orientation[2];
				bindPoseRowMajor[9] = bones[i].orientation[6];
				bindPoseRowMajor[10] = bones[i].orientation[10];
				bindPoseRowMajor[11] = 0;

				// column 4
				/*bindPoseRowMajor[12] = bones[i].orientation[3];
				bindPoseRowMajor[13] = bones[i].orientation[7];
				bindPoseRowMajor[14] = bones[i].orientation[11];
				bindPoseRowMajor[15] = 1;*/
				bindPoseRowMajor[12] = 0;
				bindPoseRowMajor[13] = 0;
				bindPoseRowMajor[14] = 0;
				bindPoseRowMajor[15] = 1;

				/// This is the original bind pose for this bone
				mat4 originalBindPose(bindPoseRowMajor);
				//originalBindPose.transpose();

				Quaternion orientation = Quaternion::fromMatrix(originalBindPose);
				orientation.z = orientation.z;
				orientation.w = orientation.w;

				vec3 position(bones[i].position.x, bones[i].position.y, bones[i].position.z);

				mat4 glBindPose = orientation.toMatrix(); // Done!
				glBindPose[12] = position.x;
				glBindPose[13] = position.y;
				glBindPose[14] = position.z;
				 
				bones[i].bindPose = glBindPose;

				// Now invert
				bones[i].inverseBindPose = bones[i].bindPose;
				bones[i].inverseBindPose.invert();

				static File outFile("matrices.txt", IODevice::TextWrite);

				//fprintf(outFile.getHandle(), "Bone %d - Quat(%f %f %f %f)\n",i, orientation.x, orientation.y, orientation.z, orientation.w);

				/*fprintf(outFile.getHandle(), "Bone %d %s inverse bind pose\n", i, bones[i].name.c_str());
				fprintf(outFile.getHandle(), "| %.7f %.7f %.7f %.7f |\n", bones[i].inverseBindPose[0], bones[i].inverseBindPose[4], bones[i].inverseBindPose[8], bones[i].inverseBindPose[12]);
				fprintf(outFile.getHandle(), "| %.7f %.7f %.7f %.7f |\n", bones[i].inverseBindPose[1], bones[i].inverseBindPose[5], bones[i].inverseBindPose[9], bones[i].inverseBindPose[13]);
				fprintf(outFile.getHandle(), "| %.7f %.7f %.7f %.7f |\n", bones[i].inverseBindPose[2], bones[i].inverseBindPose[6], bones[i].inverseBindPose[10], bones[i].inverseBindPose[14]);
				fprintf(outFile.getHandle(), "| %.7f %.7f %.7f %.7f |\n\n", bones[i].inverseBindPose[3], bones[i].inverseBindPose[7], bones[i].inverseBindPose[11], bones[i].inverseBindPose[15]);*/
				/*
				//Log("Bone %d (%s). (%f, %f, %f)", i, bones[i].name.c_str(), bones[i].position.x,bones[i].position.y,bones[i].position.z);
				fprintf(outFile.getHandle(), "Bone %d (%s). (%f, %f, %f)\n\n", i, bones[i].name.c_str(), bones[i].position.x,bones[i].position.y,bones[i].position.z);
			*/}
		}

		// Version two contains bone IDs.
		if (version == 2)
		{
			Uint32 numBoneIDs;
			dstream >> numBoneIDs;
			//Log("Num bone IDs: %d", numBoneIDs);

			boneIndexToActualBone.resize(numBoneIDs);

			for(int i = 0; i < numBoneIDs; ++i)
			{
				Uint32 boneID;
				dstream >> boneID;
				//Log("Bone ID: %d", boneID);
				boneIndexToActualBone[i] = boneID;
			}
		}
	}

	int findIDByName(String name)
	{
		for(int i = 0; i < bones.size(); ++i)
		{
			if(bones[i].name == name)
				return bones[i].id;
		}

		return -1;
	}
};

static void convertSKLToSkeleton(SkeletonSKL& skl, Skeleton& skeleton)
{
	skeleton.bones.resize(skl.bones.size());

	for(size_t i = 0; i < skeleton.bones.size(); ++i)
	{
		skeleton.bones[i].id = skl.bones[i].id;
		skeleton.bones[i].parentId = skl.bones[i].parentID;
		skeleton.bones[i].bindPoseMatrix = skl.bones[i].inverseBindPose;
		skeleton.bones[i].name = skl.bones[i].name;
		//skeleton.bones[i].bindPosePosition = skl.bones[i].position;
		//skeleton.bones[i].bindPoseOrientation = skl.bones[i].;
		//skeleton.bones[i].bindPoseScale = skl.bones[i].scale;

		//Log("Skeleton bone: %d, %s", i, skeleton.bones[i].name.c_str());
	}
}


#endif // SKLLoader_h__
