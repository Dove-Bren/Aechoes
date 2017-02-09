// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "Lrid.h"

ULrid::ULrid()
{
	MaxLen = 0;
	Owner = nullptr;
}

int32 ULrid::GetMaxLen()
{
	return MaxLen;
}

ALivingCharacter * ULrid::GetOwner()
{
	return Owner;
}

void ULrid::SetOwner(ALivingCharacter * NewOwner)
{
	this->Owner = NewOwner;
}

void ULrid::SetMaxLength(int32 length)
{
	this->MaxLen = length;
}

void ULrid::Update()
{

	//Quickly validate data
	if (MaxLen == 0 || Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to update Lrid object due to unset data"));
		return;
	}
		

	//TODO: Cache results instead of wiping them
	PathMap.Empty();
	TMap<GridPosition, uint32> lowestCost;
	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	FVector loc = Owner->GetActorLocation();

	lowestCost.Add(GridPosition::from(loc.X, loc.Y, grid->getScale()), 0);
	TArray<GridPosition> stack;
	
	stack.Add(GridPosition::from(loc.X, loc.Y, grid->getScale()));

	GridPosition cur;
	while (stack.Num() > 0) {
		cur = stack.Pop(false);
		VisitCell(&stack, &lowestCost, cur);
	}

	UE_LOG(LogTemp, Warning, TEXT("Finished Lrid update"));
}

uint32 ULrid::GetLowest(TMap<GridPosition, uint32> *map, GridPosition pos)
{
	uint32 *ret = map->Find(pos);
	if (ret == nullptr)
		return ULrid::DEFAULT_DIST;

	return *ret;
}

void ULrid::VisitCell(TArray<GridPosition> *stack, TMap<GridPosition, uint32> *LowestMap, GridPosition pos)
{

}
