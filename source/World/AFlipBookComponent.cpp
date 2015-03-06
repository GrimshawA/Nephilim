#include <Nephilim/World/AFlipBookComponent.h>

#include <json/json.h>

NEPHILIM_NS_BEGIN

/// Load the animation from a JSON file
bool FlipBookAnimation::loadfromFile(const String& filename)
{
	Json::Reader AnimationFileReader;
	Json::Value  AnimationRootValue;
	bool result = AnimationFileReader.parse(filename.c_str(), AnimationRootValue, true);
	if (result)
	{
		AnimationRootValue = AnimationRootValue["Animation"];

		String Name = AnimationRootValue["Name"].asString();
		Json::Value KeyFramesArray = AnimationRootValue["KeyFrames"];
		for (auto KeyFrameValue : KeyFramesArray)
		{
			String TextureName = KeyFrameValue["Texture"].asString();
		}

		return true;
	}
	else
		return false;
}

/// Find the correct keyframe data for the requested time
FlipBookAnimation::KeyFrame FlipBookAnimation::getFrameAtTime(float t)
{
	std::size_t index = 0;
	for (std::size_t i = 0; i < keyFrames.size(); ++i)
	{
		if (t >= keyFrames[i].t)
			index = i;
	}

	return keyFrames[index];
}

/// Add a new frame to the animation
void FlipBookAnimation::addFrame(Texture2D* texture, float keyTime)
{
	KeyFrame kF;
	kF.t = keyTime;
	kF.texture = texture;
	keyFrames.push_back(kF);
}

/// Get duration of this animation
float FlipBookAnimation::getDuration()
{
	if (keyFrames.empty())
		return 0.f;
	else
		return keyFrames[keyFrames.size() - 1].t;
}

//////////////////////////////////////////////////////////////////////////

AFlipBookComponent::AFlipBookComponent()
{
	currentKeyFrame.texture = nullptr;

}

/// Set the current animation this flip book is executing
void AFlipBookComponent::setAnimation(FlipBookAnimation* animation)
{
	currentAnimation = animation;
	elapsedTime = 0.f;
}

/// Update the animation with a delta time
void AFlipBookComponent::update(float deltaTime)
{
	if (currentAnimation)
	{
		elapsedTime += deltaTime;

		if (elapsedTime >= currentAnimation->getDuration() && currentAnimation->Looping)
		{
			elapsedTime -= currentAnimation->getDuration();
		}

		FlipBookAnimation::KeyFrame Frame = currentAnimation->getFrameAtTime(elapsedTime);
		currentKeyFrame = Frame;
	}
}

NEPHILIM_NS_END