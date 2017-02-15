// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "CollisionQueryParams.h"
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
		/*
		Add collision boxes on cells with obstacles.
		Then raytrace, ignoring the givne actor (and other actors if possible)
		Make the collision boxes slightly smaller than scale X scale
		*/

		//Collect all cells for easy iteration
		TArray<GridPosition> HotCells;

		//start at one end in the middle, with width 1. then +2, +2, etc until
		// reaches middle of grid with width 2W + 1. Ignore center cell. Reflect
		//pos's to get bottom pieces
		int32 centerx = HomePos.x, centery = HomePos.y;
		int32 rowx, rowy, yoffset;
		GridPosition pos;
		int index, len;
		len = 1;
		for (index = MaxLen; index > 0; index--) {
			//TODO as we add each cell, check grid and make collision box!!!!!!!!!!!!!!!!!!

			//calculate y difference between twin columns
			yoffset = -2 * index;

			//shift -x by (len-1)/2. Get -x,+y offset. Build by x++
			//effectively building each column from south to north
			rowy = index + centery;
			rowx = centerx - ((len - 1) / 2);
			for (int i = 0; i < len; i++) {
				pos = GridPosition(rowx + i, rowy);
				HotCells.Add(pos);
				SpawnCollisionbox(grid, pos);

				pos.y += yoffset;
				//HotCells.Add(GridPosition(rowx + i, rowy + yoffset));
				HotCells.Add(pos);
				SpawnCollisionbox(grid, pos);
			}

			//increment length, as each cell closer gives +2 cells in column
			len += 2;
		}

		//now handle middle column; go maxLen in both + and - x
		for (index = 1; index <= MaxLen; index++) {
			pos = GridPosition(centerx + index, centery);
			HotCells.Add(pos);
			SpawnCollisionbox(grid, pos);

			pos.x -= index * 2;
			//HotCells.Add(GridPosition(centerx - index, centery));
			HotCells.Add(pos);
			SpawnCollisionbox(grid, pos);
		}

		//now we'd do raytracing.
		//TODO

		//To test, gonna just use HotCells to see if they're doing what they should be
		this->AcceptablePositions = HotCells;
	}

}

TArray<GridPosition> const ULosLrid::GetEndpoints() const
{
	return AcceptablePositions;
}

void ULosLrid::SpawnCollisionbox(UWorldGrid *grid, GridPosition pos)
{
	;
}

bool ULosLrid::DoRaytrace(UWorldGrid *grid, GridPosition from, GridPosition to)
{
	return true;
}