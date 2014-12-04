// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.


#pragma once
#include "Particles/RotationRate/ParticleModuleRotationRateBase.h"
#include "ParticleModuleMeshRotationRateMultiplyLife.generated.h"

UCLASS(editinlinenew, hidecategories=Object, meta=(DisplayName = "Mesh Rotation Rate * Life"))
class UParticleModuleMeshRotationRateMultiplyLife : public UParticleModuleRotationRateBase
{
	GENERATED_UCLASS_BODY()

	/**
	 *	The scale factor that should be applied to the rotation rate.
	 *	The value is retrieved using the RelativeTime of the particle.
	 */
	UPROPERTY(EditAnywhere, Category=Rotation)
	struct FRawDistributionVector LifeMultiplier;


	//Begin UObject Interface
	virtual void	PostInitProperties() override;
	//End UObject Interface

	// Begin UParticleModule Interface
	virtual void	Spawn(FParticleEmitterInstance* Owner, int32 Offset, float SpawnTime, FBaseParticle* ParticleBase) override;
	virtual void	Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime) override;
	virtual void SetToSensibleDefaults(UParticleEmitter* Owner) override;
	// End UParticleModule Interface
};



