// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractLrid.h"
#include "LosLrid.generated.h"

/**
 * Local grid navigation class. Contains logic for moving or getting LoS
 */
UCLASS()
class AECHOES_API ULosLrid : public UAbstractLrid
{
	GENERATED_BODY()
		

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
	virtual TArray<GridPosition> GetEndpoints() override;

	
};