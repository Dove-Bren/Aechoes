// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "Engine/GameInstance.h" 
#include "AechoesGlobals.h"

UAechoesGlobals::UAechoesGlobals()
{
	;
}

UAechoesGlobals *UAechoesGlobals::Fetch(UWorld *ref)
{

	if (!ref)
		ref = GEngine->GetWorld();

	if (ref)
		return Cast<UAechoesGlobals>(ref->GetGameInstance());

	return nullptr;
}

void UAechoesGlobals::SetGrid(UWorldGrid *grid)
{
	WorldGrid = grid;
}

UWorldGrid *UAechoesGlobals::GetGrid()
{
	return WorldGrid;
}


