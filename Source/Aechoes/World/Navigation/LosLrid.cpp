// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "LosLrid.h"

ULosLrid::ULosLrid() : UAbstractLrid::UAbstractLrid()
{
	;
}

void ULosLrid::Update()
{


	//if (SMeshComp != nullptr) {
	//	SMeshComp->UnregisterComponent();
	//	SMeshComp = nullptr;
	//}

	////Quickly validate data
	//if (MaxLen == 0 || Owner == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("Unable to update Lrid object due to unset data"));
	//	return;
	//}
	//	

	////TODO: Cache results instead of wiping them
	//PathMap.Empty();
	//TMap<GridPosition, int32> lowestCost;
	//TMap<GridPosition, TArray<GridPosition>> ScratchMap;
	//UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	//FVector loc = Owner->GetEffectiveLocation();//GetActorLocation();
	//TArray<GridPosition> tAr;
	//GridPosition HomePos = GridPosition::from(loc.X, loc.Y, grid->getScale());
	//tAr.Add(HomePos);

	//lowestCost.Add(HomePos, 0);
	//PathMap.Add(HomePos, tAr);
	//


	//while (VisitCell(&lowestCost, &ScratchMap, grid)) {};

	///*UE_LOG(LogTemp, Warning, TEXT("Finished Lrid update"));

	//TArray<GridPosition> keys;
	//PathMap.GetKeys(keys);
	//for (GridPosition key : keys) {
	//	UE_LOG(LogTemp, Warning, TEXT("For [%d, %d]:"), key.x, key.y);
	//	for (GridPosition pos : *PathMap.Find(key))
	//		UE_LOG(LogTemp, Warning, TEXT(" > (%d, %d)"), pos.x, pos.y);
	//}*/
}

TArray<GridPosition> ULosLrid::GetEndpoints()
{
	return TArray<GridPosition>();
}