#include <Nephilim/World/CSkeletalMesh.h>

#include <Nephilim/Geometry.h>
#include <Nephilim/CGL.h>

#include <lolimporterx/SKNLoader.h>
#include <lolimporterx/SKLLoader.h>
#include <lolimporterx/ANMLoader.h>
#include <lolimporterx/FileWriter.h>

NEPHILIM_NS_BEGIN

CSkeletalMesh::CSkeletalMesh()
{	
	rigShader.loadShaderFromFile(Shader::VertexUnit, String("Shaders\\rigged.vs"));
	rigShader.loadShaderFromFile(Shader::FragmentUnit, String("Shaders\\rigged.fs"));
	rigShader.addAttributeLocation(0, "vertex");
	rigShader.addAttributeLocation(1, "color");
	rigShader.addAttributeLocation(2, "texCoord");
	rigShader.addAttributeLocation(3, "in_Normal");
	rigShader.addAttributeLocation(4, "in_BoneID");
	rigShader.addAttributeLocation(5, "in_Weights");

	if(rigShader.create())
	{
		Log("Rigging shader created");
	}
	rigShader.bind();

	// Setup one animation
	loadAnimation("Models\\VAYNE\\Vayne_run.anm", "Models\\VAYNE\\skeleton.skl");
}

void CSkeletalMesh::loadAnimation(const String& filename, const String& skeletonName)
{
	Log("CSkeletalMesh Anim: %s", filename.c_str());
	Log("CSkeletalMesh Skel: %s", skeletonName.c_str());

	// Important or animation doesn't work
	SkeletonSKL skeletonskl;
	skeletonskl.Load(skeletonName);
	convertSKLToSkeleton(skeletonskl, modelSkeleton);

	// Now the actual animation

	clip.clear();

	AnimationANM ax; ax.Load(filename);
	convertANMToClip(ax, clip);

	mAnimationTime = 0.f;
	mAnimationDuration = (float)ax.numFrames / ax.playbackFPS;
}

vec3 getAbsolutePosition(AnimationClip& animationClip, Skeleton& skeleton, int frame, int bone_index)
{
	int correspondentAnimationTrack = animationClip.getTrackIndexByName(skeleton.bones[bone_index].name);

	vec3 p = animationClip.tracks[correspondentAnimationTrack].frames[frame].position;

	if(skeleton.bones[bone_index].parentId >= 0)
	{
		p = getAbsolutePosition(animationClip, skeleton, frame, skeleton.bones[bone_index].parentId) + p;
	}

	return p;
}

Quaternion getAbsoluteRotation(AnimationClip& animationClip, Skeleton& skeleton, int frame, int bone_index)
{
	int correspondentAnimationTrack = animationClip.getTrackIndexByName(skeleton.bones[bone_index].name);

	Quaternion p = animationClip.tracks[correspondentAnimationTrack].frames[frame].orientation;

	if(skeleton.bones[bone_index].parentId >= 0)
	{
		p = getAbsoluteRotation(animationClip, skeleton, frame, skeleton.bones[bone_index].parentId) * p;
	}

	return p;
}

mat4 getAbsoluteTransform(AnimationClip& animationClip, Skeleton& skeleton, int frame, int bone_index)
{
	int correspondentAnimationTrack = animationClip.getTrackIndexByName(skeleton.bones[bone_index].name);

	vec3 localPosition = animationClip.tracks[correspondentAnimationTrack].frames[frame].position;

	mat4 boneRotation = Quaternion(animationClip.tracks[correspondentAnimationTrack].frames[frame].orientation.x, animationClip.tracks[correspondentAnimationTrack].frames[frame].orientation.y, animationClip.tracks[correspondentAnimationTrack].frames[frame].orientation.z, animationClip.tracks[correspondentAnimationTrack].frames[frame].orientation.w).toMatrix();
	boneRotation[12] = localPosition.x;
	boneRotation[13] = localPosition.y;
	boneRotation[14] = localPosition.z;

	int parentID = skeleton.bones[bone_index].parentId;

	if(parentID >= 0)
	{
		boneRotation = getAbsoluteTransform(animationClip, skeleton, frame, parentID) * boneRotation;
	}

	return boneRotation;
}

mat4 InterpolateMatrix(mat4 a, mat4 b, float blend)
{
	vec3 translationA(a[12], a[13], a[14]);
	vec3 translationB(b[12], b[13], b[14]);

	Quaternion rotA = Quaternion::fromMatrix(a);
	Quaternion rotB = Quaternion::fromMatrix(b);

	vec3 translationC = vec3::lerp(translationA, translationB, blend);
	Quaternion rotC = Quaternion::slerp(rotA, rotB, blend);

	mat4 r = rotC.toMatrix();
	r[12] = translationC.x;
	r[13] = translationC.y;
	r[14] = translationC.z;

	return r;
}

void CSkeletalMesh::update(const Time& deltaTime)
{
	mAnimationTime += deltaTime.asSeconds() * clip.playbackFramesPerSecond;
	if(mAnimationTime > clip.numFrames)
	{
		mAnimationTime -= clip.numFrames;
	}

	int currentFrame = (int)mAnimationTime;
	int nextFrame = (currentFrame + 1) % clip.numFrames;
	float blend = mAnimationTime - currentFrame;

	//Log("frames %d, frame time %f\nCurrent: %d\nNext: %d\nBlend %f", clip.numFrames, mAnimationTime, currentFrame, nextFrame, blend);

	// For each bone of the skeleton, get its final matrix
	/*for(std::size_t i = 0; i < modelSkeleton.bones.size(); ++i)
	{
		vec3 position = vec3::lerp(getAbsolutePosition(clip, modelSkeleton, currentFrame, i), getAbsolutePosition(clip, modelSkeleton, nextFrame, i), blend);
		Quaternion rotation = Quaternion::slerp(getAbsoluteRotation(clip, modelSkeleton, currentFrame, i), getAbsoluteRotation(clip, modelSkeleton, nextFrame, i), blend);

		mat4 currentTransform = getAbsoluteTransform(clip, modelSkeleton, currentFrame, i);
		mat4 nextTransform = getAbsoluteTransform(clip, modelSkeleton, nextFrame, i);

		mat4 boneMatrix = InterpolateMatrix(currentTransform, nextTransform, blend);

		boneTransforms[i] = boneMatrix * modelSkeleton.bones[i].bindPoseMatrix;
	}*/

	// I have all the local transforms, interpolated for all bones, just need the absolutes now
	std::vector<mat4> bone_transforms(128);

	// Fetch the local bone space transforms
	clip.getTransformsFromTime(mAnimationTime, bone_transforms);

	// Convert to world space
	modelSkeleton.convertToWorldSpace(bone_transforms);

	/// This code is correct, it assigns the final bind pose to whatever was in there
	for(std::size_t i = 0; i < clip.tracks.size(); ++i)
	{
		int bone_index = modelSkeleton.getIndexFromName(clip.tracks[i].name);

		bone_transforms[i] = bone_transforms[i] * modelSkeleton.bones[bone_index].bindPoseMatrix;
	}
	
	/// This code is correct, it assigns the final matrices just fine
	for(std::size_t i = 0; i < modelSkeleton.bones.size(); ++i)
	{
		int index = clip.getTrackIndexByName(modelSkeleton.bones[i].name);
		boneTransforms[i] = bone_transforms[index];
	}
}

void CSkeletalMesh::render(GraphicsDevice* mRenderer)
{
	//championTexture.bind();

	mRenderer->setShader(rigShader);
	mRenderer->setModelMatrix(mRenderer->getModelMatrix());
	mRenderer->setProjectionMatrix(mRenderer->getProjectionMatrix());
	mRenderer->setViewMatrix(mRenderer->getViewMatrix());

	/*mat4 boneTransforms[128];
	for(int i = 0; i < 128; ++i)
		boneTransforms[i] = mat4::identity;

	// update the transforms with the animation
	getBoneTransforms(boneTransforms, animations, skeletonskl);
	*/
	int location = glGetUniformLocation(rigShader.m_id, "u_BoneTransform");
	glUniformMatrix4fv(location, 128, false, reinterpret_cast<float*>(&boneTransforms[0]));

	if(location == -1)
	{
		//Log("Invalid uniform array");
	}

	mRenderer->draw(champion);
	mRenderer->setDefaultShader();
}

NEPHILIM_NS_END