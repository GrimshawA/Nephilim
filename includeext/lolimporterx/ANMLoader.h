#ifndef ANMLoader_h__
#define ANMLoader_h__

#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>
using namespace nx;

#include "SKLLoader.h"

class AnimatedBoneFrame
{
public:
	vec4 quaternion;
	vec3 position;
};

class AnimatedBone
{
public:
	String name;

	std::vector<AnimatedBoneFrame> frames;
};

class AnimationANM
{
public:

	String id;
	Uint32 version;

	Uint32 magic;
	Uint32 numBones;
	Uint32 numFrames;
	Uint32 playbackFPS;

	std::vector<AnimatedBone> bones; /// List of animated bones

	void Load(const String& filename)
	{
		File myFile(filename, IODevice::BinaryRead);

		if(!myFile)
			return;

		DataStream dstream(myFile);

		for(int i = 0; i < 8; i++)
			id += dstream.readChar();

		dstream >> version;

		Log("Loaded ANM %s (%d) - %s", id.c_str(), version, filename.c_str());

		dstream >> magic >> numBones >> numFrames >> playbackFPS;

		Log("ANM has %d bones and %d frames", numBones, numFrames);

		bones.resize(numBones);

		// Read animation on each bone
		for(int i = 0; i < numBones; ++i)
		{
			for(int j = 0; j < 32; j++)
				bones[i].name += dstream.readChar();

			//Log("ANM: Bone name: %s", bones[i].name.c_str());

			Uint32 unknownInteger; dstream >> unknownInteger;

			// Frames now
			bones[i].frames.resize(numFrames);
			for(int j = 0; j < numFrames; ++j)
			{
				dstream >> bones[i].frames[j].quaternion.x;
				dstream >> bones[i].frames[j].quaternion.y;
				dstream >> bones[i].frames[j].quaternion.z;
				dstream >> bones[i].frames[j].quaternion.w;

				dstream >> bones[i].frames[j].position.x;
				dstream >> bones[i].frames[j].position.y;
				dstream >> bones[i].frames[j].position.z;
			}
		}
	}

	mat4 getAbsoluteTransform(int bone_index, SkeletonSKL& skeleton, int frame_index)
	{
		// get the true bone_index in the animation
		//bone_index = skeleton.findIDByName(skeleton.bones[bone_index].name);

		// Local position of the bone
		vec3 localPosition = bones[bone_index].frames[frame_index].position;

		mat4 boneRotation = Quat(bones[bone_index].frames[frame_index].quaternion.x, bones[bone_index].frames[frame_index].quaternion.y, bones[bone_index].frames[frame_index].quaternion.z, bones[bone_index].frames[frame_index].quaternion.w).toMatrix();
		boneRotation[12] = localPosition.x;
		boneRotation[13] = localPosition.y;
		boneRotation[14] = localPosition.z;

		// This animation bone name as an index to get the parent in the skeleton
		int parentID = skeleton.bones[skeleton.findIDByName(bones[bone_index].name)].parentID;

		mat4 absoluteBoneAnimation = boneRotation;

		// Need to compute with parent's transform
		if(parentID >= 0)
		{
			absoluteBoneAnimation = getAbsoluteTransform(NameToIndex(skeleton.bones[parentID].name), skeleton, frame_index) * absoluteBoneAnimation;
		}

		return absoluteBoneAnimation;  
	}

	int NameToIndex(String name)
	{
		// From a bone name, return the index to it
		for(size_t i = 0; i < bones.size(); ++i)
		{
			if(bones[i].name == name)
				return i;
		}

		return 0; // FAILURE
	}
};

static void convertANMToClip(AnimationANM& anm, AnimationClip& clip)
{
	// Allocate N tracks of animation, one per bone	
	clip.tracks.resize(anm.bones.size());

	clip.numFrames = anm.numFrames;

	for(size_t i = 0; i < clip.tracks.size(); ++i)
	{		
		clip.tracks[i].name = anm.bones[i].name;
		clip.tracks[i].frames.resize(anm.bones[i].frames.size());

		for(size_t j = 0; j < clip.tracks[i].frames.size(); ++j)
		{
			clip.tracks[i].frames[j].scale = vec3(1.f, 1.f, 1.f);
			clip.tracks[i].frames[j].position = anm.bones[i].frames[j].position;
			clip.tracks[i].frames[j].orientation = Quat(anm.bones[i].frames[j].quaternion.x, anm.bones[i].frames[j].quaternion.y, anm.bones[i].frames[j].quaternion.z, anm.bones[i].frames[j].quaternion.w);
			clip.tracks[i].frames[j].time = (1.f / anm.playbackFPS) * j;
		}
	}

	clip.playbackFramesPerSecond = anm.playbackFPS;
}

#endif // ANMLoader_h__
