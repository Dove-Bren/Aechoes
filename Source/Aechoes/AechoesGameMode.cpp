// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "AechoesGameMode.h"
#include "Character/AechoesCharacter.h"

AAechoesGameMode::AAechoesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Actors/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    this->grid = NewObject<UWorldGrid>();


}

UWorldGrid * AAechoesGameMode::getGrid()
{
    return this->grid;
}
