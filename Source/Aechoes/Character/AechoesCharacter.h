// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
//#include "GameFramework/Character.h"
#include "../World/Obstacle.h"
#include "../Control/OverworldCharMovementComponent.h"
#include "../Control/OCharacterController.h"
#include "AechoesCharacter.generated.h"

UCLASS(config=Game)
class AAechoesCharacter : public AObstacle
{
	GENERATED_BODY()

public:
	AAechoesCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	/////// Obstacle API ////////////
	/**
	* Checks whether this blocks _movement_ for the given character
	* @param cin the character trying to move past this obstacle
	* @return true when the character can pass
	**/
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Movement")
	virtual bool CanPass(AAechoesCharacter *cin) override;
		//virtual bool CanPass_Implementation(AAechoesCharacter *cin) override;

	/**
	* Checks whether this blocks _sight_ for the given character
	* @param char the character trying to see/cast through this obstacle
	* @param cast whether this check is used for LOS instead of just sight
	* @return true when the character can see through
	**/
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Movement")
	virtual bool CanSeeThrough(AAechoesCharacter *cin, bool cast) override;
		//virtual bool CanSeeThrough_Implementation(AAechoesCharacter *cin, bool cast) override;

};

