// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PawnMovementComponent.h"
#include "OverworldCameraMovement.generated.h"

UCLASS(config=Control)
class UOCameraMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

protected:
	float const STAT_CAMERA_MINZ = 200.0f;
	float const STAT_CAMERA_MAXZ = 2000.0f;
	float const STAT_CAMERA_MAXPAN = 2000.0f;
  float const STAT_CAMERA_MINPITCH = 20.0f;

	AActor *focus;

	
public:
    UOCameraMovement();

	void setFocus(AActor *newFocus);

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};

