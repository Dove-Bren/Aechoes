// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "AechoesGameMode.h"
#include "Character/AechoesCharacter.h"
#include "Control/OverworldCamera.h"

AAechoesGameMode::AAechoesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Actors/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    this->grid = NewObject<UWorldGrid>();
    //this->camera = NewObject<AOverworldCamera>();

   

}

UWorldGrid * AAechoesGameMode::getGrid()
{
    return this->grid;
}

void AAechoesGameMode::StartPlay()
{
	this->camera = GetWorld()->SpawnActor<AOverworldCamera>(
	AOverworldCamera::StaticClass(),
	FVector(-800.0f, 190.0f, 200.0f),
	FRotator(0.0f, 0.0f, 0.0f));
}
