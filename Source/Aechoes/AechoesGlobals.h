// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "World/WorldGrid.h"
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

protected:
	/** Game Grid Reference **/
	UWorldGrid *WorldGrid;

public:

	/** Set game grid for use globally **/
	void SetGrid(UWorldGrid *grid);

	/** Return the current game grid **/
	UWorldGrid *GetGrid();
	
	
};
