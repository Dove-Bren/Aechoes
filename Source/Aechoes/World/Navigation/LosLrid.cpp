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
		//Hold references to created collision boxes for cleanup
		TArray<UBoxComponent *> ColBoxes;
		//Keep track of which actors to ignore
		TArray<AActor *> IActors;

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

				SetupGridPosition(grid, HotCells, ColBoxes, IActors, pos);
				/*if (grid->get(pos) != nullptr)
					SpawnCollisionbox(grid, ColBoxes, pos);
				else
					HotCells.Add(pos);*/

				pos.y += yoffset;
				//HotCells.Add(GridPosition(rowx + i, rowy + yoffset));

				SetupGridPosition(grid, HotCells, ColBoxes, IActors, pos);
				/*if (grid->get(pos) != nullptr)
					SpawnCollisionbox(grid, ColBoxes, pos);
				else
					HotCells.Add(pos);*/
			}

			//increment length, as each cell closer gives +2 cells in column
			len += 2;
		}

		//now handle middle column; go maxLen in both + and - x
		for (index = 1; index <= MaxLen; index++) {
			pos = GridPosition(centerx + index, centery);
/*
			if (grid->get(pos) != nullptr)
				SpawnCollisionbox(grid, ColBoxes, pos);
			else
				HotCells.Add(pos);*/
			SetupGridPosition(grid, HotCells, ColBoxes, IActors, pos);

			pos.x -= index * 2;
			//HotCells.Add(GridPosition(centerx - index, centery));
			/*if (grid->get(pos) != nullptr)
				SpawnCollisionbox(grid, ColBoxes, pos);
			else
				HotCells.Add(pos);*/
			SetupGridPosition(grid, HotCells, ColBoxes, IActors, pos);
		}

		////To test, gonna just use HotCells to see if they're doing what they should be
		//this->AcceptablePositions = HotCells;

		if (!IgnoreLOS) {
			FCollisionQueryParams params;
			params.AddIgnoredActors(IActors);

			for (GridPosition p : HotCells) {
				if (!DoRaytrace(grid, params, HomePos, p))
					AcceptablePositions.Add(p);
			}
		}

		//Clear out collision cells, since we don't need them anymore
		if (ColBoxes.Num() > 0)
		for (UBoxComponent *box : ColBoxes) {
			box->UnregisterComponent();
		}
		ColBoxes.Empty();
	}

}

void ULosLrid::SetupGridPosition(UWorldGrid *grid, TArray<GridPosition> &HotCells,
	TArray<UBoxComponent*> & CollisionBoxes, TArray<AActor *> & IActors, GridPosition pos)
{

	//if IgnoreLOS is true, just make it a box since we can reach it
	if (IgnoreLOS) {
		HotCells.Add(pos);
		return;
	}

	//if GET is null, add hotcell right away.
	//if not, depends on the obstacle returned
	//  if we can see through it, do nothing; no hotcell, but no coll box
	//  if we can't see through it, add a box

	if (grid->get(pos) != nullptr) {
		AObstacle *obj = grid->get(pos);
		if (obj->CanSeeThrough(Owner, true))
			; //do nothing
		else
			SpawnCollisionbox(grid, CollisionBoxes, pos);

		IActors.Add(obj);
	}
	else
		HotCells.Add(pos);
}

TArray<GridPosition> const ULosLrid::GetEndpoints() const
{
	return AcceptablePositions;
}

void ULosLrid::SpawnCollisionbox(UWorldGrid *grid, TArray<UBoxComponent*> & CollisionBoxes, GridPosition pos)
{
	FVector wPos = grid->ToWorldPos(pos, true, true);
	wPos.Z += ((float)ULosLrid::RAYTRACE_ZOFFSET) / 2.0f;
	FVector extent((grid->getScale() / 2.0f) - 0.02f, (grid->getScale() / 2.0f) - 0.02f, ((float) ULosLrid::RAYTRACE_ZOFFSET) / 2.0f);
	UBoxComponent *box = NewObject<UBoxComponent>(this);
	box->SetRelativeLocation(wPos);
	box->InitBoxExtent(extent);
	//box->SetVisibility(true);
	box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	box->RegisterComponent();
	box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);


	CollisionBoxes.Add(box);
}

bool ULosLrid::DoRaytrace(UWorldGrid *grid, FCollisionQueryParams &cParams, GridPosition from, GridPosition to)
{
	FVector vFrom = grid->ToWorldPos(from, true, true),
		vTo = grid->ToWorldPos(to, true, true);
	vFrom.Z += ((float)ULosLrid::RAYTRACE_ZOFFSET) / 2.0f;
	vTo.Z += ((float)ULosLrid::RAYTRACE_ZOFFSET) / 2.0f;

	FHitResult res;
	GetWorld()->DebugDrawTraceTag = FName("KEY");
	return GetWorld()->LineTraceSingleByChannel(res, vFrom, vTo, ECollisionChannel::ECC_Visibility,
		cParams);

}

void ULosLrid::CheckLOS(bool check)
{
	this->IgnoreLOS = !check;
}