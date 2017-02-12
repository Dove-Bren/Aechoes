// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "../Control/OverworldCharMovementComponent.h"
#include "../Control/OCharacterController.h"
#include "AechoesCharacter.generated.h"

UCLASS(config=Game)
class AAechoesCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAechoesCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};

