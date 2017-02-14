// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>

#include "AbstractLrid.h"
#include "../Obstacle.h"
#include "Lrid.generated.h"

/**
 * Local grid navigation class. Contains logic for moving or getting LoS
 */
UCLASS()
class AECHOES_API ULrid : public UAbstractLrid
{
	GENERATED_BODY()

public:
	static uint32 const DEFAULT_DIST = 999999;

protected:

	/** Map of paths to the given position -- since last update **/
	TMap<GridPosition, TArray<GridPosition>> PathMap;

	/** Return the output of the heuristic function for the given input **/
	virtual int32 GetHeuristic(GridPosition targ);

	/** 
	 * Check whether a given cell can be pathed to 
	 * @param GridRef
	 * @param FromCell the cell we're going from
	 * @param ToCell 
	 * @return whether the given transition is legal
	 **/
	virtual bool CanMove(UWorldGrid *GridRef, GridPosition FromCell, GridPosition ToCell);

private:
	/** Get lowest cost of a specific position during iteration **/
	static int32 GetLowest(TMap<GridPosition, int32> *map, GridPosition pos);

	/** Recursive method. Visit the given cell, adding cells as neccessary **/
	bool VisitCell(TMap<GridPosition, int32> *LowestMap, TMap<GridPosition, TArray<GridPosition>> *workingMap,
		UWorldGrid *Grid);

public:

	ULrid();

	/**
	* Performs an update of this grid. This involves recalculating all paths, etc.
	* This method is intended to be called only when needed -- when correct local path
	* information is needed.
	* As of writing this, this method doesn't perform any caching or cross-call
	* optimizations of kind. #FutureWork
	**/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void Update() override;

	/**
	 * Uses information gained in the last #Update to return the shortest
	 * found path to the target location.
	 * If the path does not exist, an empty TArray is returned instead
	 * @param TargetPos the location to look up path info to
	 * @return TArray with each point in the path, or an empty array if no path exists
	 **/
	virtual TArray<GridPosition> GetPath(GridPosition TargetPos);

	/**
	* Returns a set of endpoints pathed to in this lrid
	* On regular movement lrid's, these are all the valid movement targets
	* @return a set with all valid points, including when there are 0
	**/
	virtual TArray<GridPosition> GetEndpoints() override;

	
};