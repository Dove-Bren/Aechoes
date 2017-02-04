// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PawnMovementComponent.h"
#include "OverworldCameraController.generated.h"

UCLASS(config=Control)
class UOverworldCameraController : public UPawnMovementComponent
{
	GENERATED_BODY()

	
public:
    UOverworldCameraController();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};

