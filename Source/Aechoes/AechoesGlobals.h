// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "World/WorldGrid.h"
#include "Combat/Attack/AttackRegistry.h"
#include "Control/UI/ActionbarLoadout.h"
#include "AechoesGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AECHOES_API UAechoesGlobals : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UAechoesGlobals();

	static UAechoesGlobals *Fetch(UWorld *ref = nullptr);

	static UWorldGrid *FetchGrid(UWorld *ref = nullptr);

protected:

	/** Game ID, for Saving and stuff **/
	uint32 GameID;

	/** Game Grid Reference **/
	UWorldGrid *WorldGrid;

	/** Attack Registry **/
	UAttackRegistry *AttackRegistry;

	/** Global storage of actionbar loadouts **/
	TMap<ACombatableCharacter *, FActionbarLoadout> ALoadoutMap;

public:

	/** Set game grid for use globally **/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetGrid(UWorldGrid *grid);

	/** Return the current game grid **/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	UWorldGrid *GetGrid();

	/** Fetch a reference to the game's attack registry **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	UAttackRegistry *GetAttackRegistry();

	/**
	 * Fetch an ABar loadout for the given character
	 * @return the ABarLoadout for the character, or nullptr if there isn't one
	 **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	FActionbarLoadout GetABarLoadout(ACombatableCharacter* key);

	/** Set the ABar loadout for the given character **/
	UFUNCTION(BlueprintCallable, Category = "Combat | Control")
	void SetABarLoadout(ACombatableCharacter* key, FActionbarLoadout loadout);

	/** Sets the game ID for this game **/
	void SetGameID(uint32 newID);

	/** Returns the currently set (if tehre is one) game ID **/
	uint32 GetGameID();
	
	
};
