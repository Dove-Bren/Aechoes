// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>

#include "../WorldGrid.h"
#include "../../Character/LivingCharacter.h"
#include "../../AechoesGameMode.h"
#include "../Obstacle.h"
#include "Lrid.generated.h"

/**
 * Local grid navigation class. Contains logic for moving or getting LoS
 */
UCLASS()
class AECHOES_API ULrid : public UActorComponent
{
	GENERATED_BODY()

public:
	static uint32 const DEFAULT_DIST = 999999;

protected:
    
    /** Maximum length of path **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Movement)
    int32 MaxLen;

	/** The character that owns this grid. Used when querying obstacles **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Movement)
	ALivingCharacter *Owner;

	/** Map of paths to the given position -- since last update **/
	TMap<GridPosition, TArray<GridPosition>> PathMap;

	/** Return the output of the heuristic function for the given input **/
	virtual int32 GetHeuristic(GridPosition targ);

private:
	/** Get lowest cost of a specific position during iteration **/
	static int32 GetLowest(TMap<GridPosition, int32> *map, GridPosition pos);

	/** Recursive method. Visit the given cell, adding cells as neccessary **/
	bool VisitCell(TMap<GridPosition, int32> *LowestMap, TMap<GridPosition, TArray<GridPosition>> *workingMap);

public:

	ULrid();
    
    /** Returns the Max Length of this grid **/
    UFUNCTION(BlueprintCallable, Category = "Movement")
    int32 GetMaxLen();

    /**
	 * Returns the character that owns this grid
     * @return the owner, including if it's null
     **/
    UFUNCTION(BlueprintCallable, Category = "Movement")
    ALivingCharacter* GetOwner();

	/**
	* Sets this grid's owner. Required for it to do any real work
	* @param NewOwner the new owner
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetOwner(ALivingCharacter *NewOwner);

	/**
	* Sets this grid's maximum length. Required for it to do any real work
	* @param length the new length
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMaxLength(int32 length);

	/**
	* Performs an update of this grid. This involves recalculating all paths, etc.
	* This method is intended to be called only when needed -- when correct local path
	* information is needed.
	* As of writing this, this method doesn't perform any caching or cross-call
	* optimizations of kind. #FutureWork
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void Update();

	
};