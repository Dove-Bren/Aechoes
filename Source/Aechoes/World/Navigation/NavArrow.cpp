// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "NavArrow.h"


// Sets default values
ANavArrow::ANavArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent *root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	this->RootComponent = root;
}

void ANavArrow::UpdateTarget(FVector NewTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("Update with input [%f, %f]"), NewTarget.X, NewTarget.Y);
	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	UpdateTarget(grid->ToGridPos(NewTarget));
}

void ANavArrow::UpdateTarget(GridPosition NewTarget)
{
	if (NewTarget == LastTarget)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Deep Input with grid pos: [%d, %d]"), NewTarget.x, NewTarget.y);

	LastTarget = NewTarget;
	if (Pieces.Num() != 0)
		Pieces.Empty();

	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	FVector loc = grid->ToWorldPos(LastTarget);
	loc = grid->snapTo(loc, true);
	UE_LOG(LogTemp, Warning, TEXT("ToWorldPos returns [%f, %f]"), loc.X, loc.Y);
	AOverworldController *GlobalController = (AOverworldController *) GetWorld()->GetFirstLocalPlayerFromController();
	/*if (GlobalController != nullptr && GlobalController->GetControl() != nullptr) {
		loc.Z = 
			GlobalController->
			GetControl()->
			GetActorLocation()
			.Z;
	}*/
	loc.Z = 120.0f;
	UNavArrowPiece *piece = NewObject<UNavArrowPHead>(this, TEXT("Arrow Head")); 
	piece->RegisterComponent();
	piece->AttachTo(RootComponent);
	//piece->RelativeLocation = loc;
	piece->SetWorldLocation(loc);
	//SetActorLocation(loc);
	
	
	/*GetWorld()->
		SpawnActor<UNavArrowPHead>(UNavArrowPHead::StaticClass(), loc, FRotator());*/

	Pieces.Add(piece);
}

GridPosition ANavArrow::GetLastTarget()
{
	return GridPosition();
}


