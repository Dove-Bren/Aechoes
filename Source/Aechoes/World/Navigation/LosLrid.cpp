// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "../../AechoesGameMode.h"
#include "LosLrid.h"

ULosLrid::ULosLrid() : UAbstractLrid::UAbstractLrid()
{
	;
}

void ULosLrid::Update()
{


	if (SMeshComp != nullptr) {
		SMeshComp->UnregisterComponent();
		SMeshComp = nullptr;
	}

	//Quickly validate data
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to update LosLrid object due to unset data"));
		return;
	}
		
	AcceptablePositions.Empty();

	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	FVector loc = Owner->GetEffectiveLocation();
	GridPosition HomePos = GridPosition::from(loc.X, loc.Y, grid->getScale());
	
	if (MaxLen == 0 || IncludeZero)
		AcceptablePositions.Add(HomePos);

	if (MaxLen > 0) {
		//visit each cell and do a raytrace
		//TODO
	}

}

TArray<GridPosition> const ULosLrid::GetEndpoints() const
{
	return AcceptablePositions;
}