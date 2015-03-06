#include <Nephilim/World/World_RTTI.h>

#include <Nephilim/Foundation/Factory.h>

#include <Nephilim/World/ACameraComponent.h>
#include <Nephilim/World/ACharacterComponent.h>
#include <Nephilim/World/AAudioComponent.h>
#include <Nephilim/World/ABoxComponent.h>
#include <Nephilim/World/AConvexShapeComponent.h>
#include <Nephilim/World/ADirectionalLightComponent.h>
#include <Nephilim/World/AInputComponent.h>
#include <Nephilim/World/AParticleEmitterComponent.h>
#include <Nephilim/World/APointLightComponent.h>
#include <Nephilim/World/AProjectedWaterComponent.h>
#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/World/AFlipBookComponent.h>
#include <Nephilim/World/AScriptComponent.h>
#include <Nephilim/World/ASkeletalMeshComponent.h>
#include <Nephilim/World/ASkyboxComponent.h>
#include <Nephilim/World/ASphereComponent.h>
#include <Nephilim/World/ASpotLightComponent.h>
#include <Nephilim/World/ASpriteComponent.h>
#include <Nephilim/World/AStaticMeshComponent.h>
#include <Nephilim/World/ATerrainComponent.h>
#include <Nephilim/World/ATextComponent.h>
#include <Nephilim/World/ATilemapComponent.h>
#include <Nephilim/World/AVoxelVolumeComponent.h>
#include <Nephilim/World/AWidgetComponent.h>

#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/World.h>
#include <Nephilim/World/Level.h>


NEPHILIM_NS_BEGIN

void RegisterWorldRTTI()
{
	REGISTER_FACTORY_CLASS("Object", Object);
	REGISTER_FACTORY_CLASS("Component", Component);

	REGISTER_FACTORY_CLASS("ACameraComponent", ACameraComponent);
	REGISTER_FACTORY_CLASS("ACharacterComponent", ACharacterComponent);
	REGISTER_FACTORY_CLASS("AAudioComponent", AAudioComponent);
	REGISTER_FACTORY_CLASS("ABoxComponent", ABoxComponent);
	REGISTER_FACTORY_CLASS("AConvexShapeComponent", AConvexShapeComponent);
	REGISTER_FACTORY_CLASS("ADirectionalLightComponent", ADirectionalLightComponent);
	REGISTER_FACTORY_CLASS("AInputComponent", AInputComponent);
	REGISTER_FACTORY_CLASS("AParticleEmitterComponent", AParticleEmitterComponent);
	REGISTER_FACTORY_CLASS("APointLightComponent", APointLightComponent);
	REGISTER_FACTORY_CLASS("AProjectedWaterComponent", AProjectedWaterComponent);
	REGISTER_FACTORY_CLASS("ASceneComponent", ASceneComponent);
	REGISTER_FACTORY_CLASS("AScriptComponent", AScriptComponent);
	REGISTER_FACTORY_CLASS("ASkeletalMeshComponent", ASkeletalMeshComponent);
	REGISTER_FACTORY_CLASS("ASkyboxComponent", ASkyboxComponent);
	REGISTER_FACTORY_CLASS("ASphereComponent", ASphereComponent);
	REGISTER_FACTORY_CLASS("ASpotLightComponent", ASpotLightComponent);
	REGISTER_FACTORY_CLASS("ASpriteComponent", ASpriteComponent);
	REGISTER_FACTORY_CLASS("AStaticMeshComponent", AStaticMeshComponent);
	REGISTER_FACTORY_CLASS("ATerrainComponent", ATerrainComponent);
	REGISTER_FACTORY_CLASS("ATextComponent", ATextComponent);
	REGISTER_FACTORY_CLASS("ATilemapComponent", ATilemapComponent);
	REGISTER_FACTORY_CLASS("AVoxelVolumeComponent", AVoxelVolumeComponent);
	REGISTER_FACTORY_CLASS("AWidgetComponent", AWidgetComponent);
	REGISTER_FACTORY_CLASS("AFlipBookComponent", AFlipBookComponent);

	REGISTER_FACTORY_SUBCLASS("ACameraComponent",    "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ACharacterComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AAudioComponent",     "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ABoxComponent",       "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AConvexShapeComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ADirectionalLightComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AInputComponent", "Component");
	REGISTER_FACTORY_SUBCLASS("AParticleEmitterComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("APointLightComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AProjectedWaterComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ASceneComponent", "Component");
	REGISTER_FACTORY_SUBCLASS("AScriptComponent", "Component");
	REGISTER_FACTORY_SUBCLASS("ASkeletalMeshComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ASkyboxComponent", "Component");
	REGISTER_FACTORY_SUBCLASS("ASphereComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ASpotLightComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ASpriteComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AStaticMeshComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ATerrainComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ATextComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("ATilemapComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AVoxelVolumeComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AWidgetComponent", "ASceneComponent");
	REGISTER_FACTORY_SUBCLASS("AFlipBookComponent", "ASceneComponent");






	REGISTER_FACTORY_CLASS("World", World);
	REGISTER_FACTORY_CLASS("Level", Level);
	REGISTER_FACTORY_CLASS("GameObject", GameObject);
	REGISTER_FACTORY_CLASS("Actor", Actor);
	REGISTER_FACTORY_SUBCLASS("Actor", "GameObject");
	REGISTER_FACTORY_SUBCLASS("GameObject", "Object");
	REGISTER_FACTORY_SUBCLASS("Level", "Object");
	REGISTER_FACTORY_SUBCLASS("World", "Object");
}

NEPHILIM_NS_END