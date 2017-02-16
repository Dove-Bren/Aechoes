// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractLrid.h"
#include "../WorldGrid.h"
#include "LosLrid.generated.h"

/**
 * Local grid navigation class. Contains logic for moving or getting LoS
 */
UCLASS()
class AECHOES_API ULosLrid : public UAbstractLrid
{
	GENERATED_BODY()

public:
	/** Height offset for 2d raytraces **/
	static const uint32 RAYTRACE_ZOFFSET = 100;
		
protected:

	/** List of acceptable positions from last update **/
	TArray<GridPosition> AcceptablePositions;
	
	/** Whether 0 is included in range 
	 * Note: This is ignored if range == 0 **/
	bool IncludeZero;

	virtual void SetupGridPosition(UWorldGrid *grid, TArray<GridPosition> &HotCells, TArray<UBoxComponent*> & CollisionBoxes, GridPosition pos);

	virtual void SpawnCollisionbox(UWorldGrid *grid, TArray<UBoxComponent*> & CollisionBoxes, GridPosition pos);

	virtual bool DoRaytrace(UWorldGrid *grid, FCollisionQueryParams &Params, GridPosition from, GridPosition to);


public:

	ULosLrid();

	/**
	* Performs an update of this grid. This involves recalculating all lines, etc.
	* This method is intended to be called only when needed -- when correct LOS
	* information is needed.
	* As of writing this, this method doesn't perform any caching or cross-call
	* optimizations of kind. #FutureWork
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void Update() override;

	/**
	* Returns a set of endpoints pathed to in this lrid
	* On regular movement lrid's, these are all the valid movement targets
	* @return a set with all valid points, including when there are 0
	**/
	virtual TArray<GridPosition> const GetEndpoints() const override;

	
};