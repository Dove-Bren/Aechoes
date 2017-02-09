// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Character/AechoesCharacter.h"
#include "Obstacle.generated.h"

/**
 * Interface class that represents something that blocks movement on a grid
 */
UCLASS()
class AECHOES_API AObstacle : public AActor
{
	GENERATED_BODY()

public:

	/**
	 * Checks whether this blocks _movement_ for the given character
	 * @param cin the character trying to move past this obstacle
	 * @return true when the character can pass
	 **/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool CanPass(AAechoesCharacter *cin);

	/**
	* Checks whether this blocks _sight_ for the given character
	* @param char the character trying to see/cast through this obstacle
	* @param cast whether this check is used for LOS instead of just sight
	* @return true when the character can see through
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool CanSeeThrough(AAechoesCharacter *cin, bool cast);
	
};