// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "World/WorldGrid.h"
#include "Control/OverworldCamera.h"
#include "AechoesGameMode.generated.h"

UCLASS(minimalapi)
class AAechoesGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
    
    /** The game grid instance **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    UWorldGrid *grid;

    /** The overworld camera **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Controls)
    AOverworldCamera *camera;

	/** Currently in a fight, or no? **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Control")
	bool InFight;

public:
	AAechoesGameMode();

	static AAechoesGameMode *Fetch(UWorld *Ref);

    /** Returns the game grid **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    UWorldGrid *getGrid();

	/** Returns the overworld game camera **/
	UFUNCTION(BlueprintCallable, Category = Camera)
	AOverworldCamera *getCamera();

	virtual void StartPlay() override;
};



