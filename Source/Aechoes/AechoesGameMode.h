// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "Combat/Control/Combatable.h"
#include "Combat/Control/Team.h"
#include "World/WorldGrid.h"
#include "Control/Camera/OverworldCamera.h"
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

	/** List of fight even listeners **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Control")
	TArray<TScriptInterface<ICombatable>> CombatListeners;
	

public:
	AAechoesGameMode();

	static AAechoesGameMode *Fetch(UWorld *Ref);

    /** Returns the game grid **/
    UFUNCTION(BlueprintCallable, Category = Combat)
    UWorldGrid *getGrid();

	/** Returns the overworld game camera **/
	UFUNCTION(BlueprintCallable, Category = Camera)
	AOverworldCamera *getCamera();

	/** Adds a listener to the list of listeners **/
	UFUNCTION(BlueprintCallable, Category = Control)
	void AddCombatListener(TScriptInterface<ICombatable> Listener);

	/** Starts a fight with the given teams **/
	UFUNCTION(BlueprintCallable, Category = Control)
	void LaunchFight(FTeam team1, FTeam team2);

	virtual void StartPlay() override;
};



