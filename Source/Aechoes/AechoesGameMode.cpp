// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Aechoes.h"
#include "AechoesGameMode.h"
#include "AechoesGlobals.h"
#include "Character/AechoesCharacter.h"
#include "Control/Movement/OverworldController.h"
#include "Control/Camera/OverworldCamera.h"

AAechoesGameMode::AAechoesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Actors/Blueprints/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AOverworldController::StaticClass();

	this->grid = CreateDefaultSubobject<UWorldGrid>(TEXT("Grid"));
  this->Clock = CreateDefaultSubobject<UCombatClock>(TEXT("Clock"));

    //this->grid = NewObject<UWorldGrid>();
    //this->camera = NewObject<AOverworldCamera>();

   

}

AAechoesGameMode *AAechoesGameMode::Fetch(UWorld *Ref)
{
  if (Ref)
	  return (AAechoesGameMode *) Ref->GetAuthGameMode();

  return nullptr;
}

UWorldGrid * AAechoesGameMode::getGrid()
{
    return this->grid;
}

AOverworldCamera *AAechoesGameMode::getCamera()
{
	return this->camera;
}

void AAechoesGameMode::StartPlay()
{


	this->camera = GetWorld()->SpawnActor<AOverworldCamera>(
	AOverworldCamera::StaticClass(),
	FVector(-800.0f, 190.0f, 300.0f),
	FRotator(0.0f, 0.0f, 0.0f));

	
	Super::StartPlay();

	//UAechoesGlobals::SetWorld(GetWorld());
	if (UAechoesGlobals::Fetch(GetWorld()))
		UAechoesGlobals::Fetch(GetWorld())->SetGrid(grid);
	else
		UE_LOG(LogTemp, Warning, TEXT("Unable to set grid"));
	
}

void AAechoesGameMode::AddCombatListener(TScriptInterface<ICombatable> Listener)
{
	CombatListeners.Add(Listener);
}

void AAechoesGameMode::LaunchFight(FTeam team1, FTeam team2)
{
	UE_LOG(LogTemp, Warning, TEXT("Launching with two teams!"));

  TArray<ACombatableCharacter *> parts;
  for (ACombatableCharacter *mem : team1.GetMemberList())
    parts.Add(mem);
  for (ACombatableCharacter *mem : team2.GetMemberList())
    parts.Add(mem);

  Clock->InitParticipants(parts);

}

UCombatClock *AAechoesGameMode::getClock()
{
  return Clock;
}