// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "World/WorldGrid.h"
#include "AechoesGameMode.generated.h"

UCLASS(minimalapi)
class AAechoesGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
    
    /** The game grid instance **/
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Combat)
    UWorldGrid *grid;

public:
	AAechoesGameMode();

    /** Returns the game grid **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    UWorldGrid *getGrid();
};



