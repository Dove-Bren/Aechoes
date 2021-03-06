// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "AI/Navigation/NavigationSystem.h"
#include "../GridCellMesh.h"
#include "../../AechoesGameMode.h"
#include "Lrid.h"

ULrid::ULrid() : UAbstractLrid::UAbstractLrid()
{
	;
}

void ULrid::Update()
{


  if (GridDisplay != nullptr) {
    GridDisplay->Destroy();
    GridDisplay = nullptr;
  }

	//Quickly validate data
	if (MaxLen == 0 || Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to update Lrid object due to unset data"));
		return;
	}
		

	//TODO: Cache results instead of wiping them
	PathMap.Empty();
	TMap<GridPosition, int32> lowestCost;
	TMap<GridPosition, TArray<GridPosition>> ScratchMap;
	UWorldGrid *grid = ((AAechoesGameMode *) this->GetWorld()->GetAuthGameMode())->getGrid();
	FVector loc = Owner->GetEffectiveLocation();//GetActorLocation();
	TArray<GridPosition> tAr;
	GridPosition HomePos = GridPosition::from(loc.X, loc.Y, grid->getScale());
	tAr.Add(HomePos);

	lowestCost.Add(HomePos, 0);
	PathMap.Add(HomePos, tAr);
	


	while (VisitCell(&lowestCost, &ScratchMap, grid)) {};

	/*UE_LOG(LogTemp, Warning, TEXT("Finished Lrid update"));

	TArray<GridPosition> keys;
	PathMap.GetKeys(keys);
	for (GridPosition key : keys) {
		UE_LOG(LogTemp, Warning, TEXT("For [%d, %d]:"), key.x, key.y);
		for (GridPosition pos : *PathMap.Find(key))
			UE_LOG(LogTemp, Warning, TEXT(" > (%d, %d)"), pos.x, pos.y);
	}*/
}

int32 ULrid::GetLowest(TMap<GridPosition, int32> *map, GridPosition pos)
{
	int32 *ret = map->Find(pos);
	if (ret == nullptr)
		return ULrid::DEFAULT_DIST;

	return *ret;
}

bool ULrid::VisitCell(TMap<GridPosition, int32> *LowestMap, TMap<GridPosition, TArray<GridPosition>> *workingMap,
	UWorldGrid *grid)
{
	/*
	Look through out map to see what we got going on. For each established
	Point, check neighbors to see if they're established. If not, get shortest. Then,
	take shortest overall point and add it as established
	*/
	//this->PathMap is established list.
	//LowestMap is shortest path for all nodes

	GridPosition minPos;
	int32 minLen = ULrid::DEFAULT_DIST;
	bool hasMin = false;

	TArray<GridPosition> curPath;

	TArray<GridPosition> keys;
	int8 i, posX[] = {-1, 0, 0, 1}, posY[] = {0, -1, 1, 0};
	int32 curDist, calc, hfCost;
	PathMap.GenerateKeyArray(keys);
	for (GridPosition cur : keys) {
		curDist = ULrid::GetLowest(LowestMap, cur);

		//don't look past ourselves if we're already at max dist
		if (curDist >= this->MaxLen)
			continue;

		curPath = *PathMap.Find(cur);

		for (i = 0; i < 4; i++) {
			//for each cell in the SWEN directions
			GridPosition targ;

			
			targ.x = cur.x + posX[i];
			targ.y = cur.y + posY[i];
			if (PathMap.Find(targ) != nullptr)
				continue;

			if (!CanMove(grid, cur, targ))
				continue;
			
			
			//This cell is not finalized. Go ahead and process it

			if (LowestMap->Find(targ) == nullptr)
				calc = ULrid::DEFAULT_DIST;
			else
				calc = *(LowestMap->Find(targ));

			//get cost from this node, with heuristic cost
			hfCost = (curDist + 1) + GetHeuristic(targ);

			if (hfCost < calc) {
				//if us+1 is less than what we have for them (or less than inf)
				LowestMap->Add(targ, hfCost);
				calc = hfCost;
				TArray<GridPosition> newPath = curPath;
				newPath.Add(targ);
				workingMap->Add(targ, newPath);
			}

			//finally, update minimum list with this cell
			if (calc < minLen) {
				minLen = calc;
				minPos = targ;
			}

			hasMin = true;
		}
	}

	//We've went through all established keys. Promote minPos to an established key
	if (!hasMin) //no cells that aren't established found
		return false;

	//WorkingPath has it's last known and final path. 
	PathMap.Add(minPos, *workingMap->Find(minPos));
	return true;
	
}

int32 ULrid::GetHeuristic(GridPosition targ)
{
	return 0; //Just Dijkstra's
}

bool ULrid::CanMove(UWorldGrid *grid, GridPosition FromCell, GridPosition ToCell)
{
	
	if (grid->get(ToCell) != nullptr) {

		//see if it's an obstacle. If so, can move?
		AObstacle *out = Cast<AObstacle>(grid->get(ToCell));

		if (out != nullptr && out->CanPass(GetOwner()))
			return true;

		return false;
	}

	//Perform nav movement check 
	//TODO cache nav lookups?
	FVector VStart, VEnd, hitLoc;
	VStart = grid->ToWorldPos(FromCell, true, true);
	VEnd = grid->ToWorldPos(ToCell, true, true);

	/*class MoveFilter : public UNavigationQueryFilter {

	} filter;*/


	if (UNavigationSystem::NavigationRaycast(GetWorld(), VStart, VEnd, hitLoc))
		return false;

	return true;
}

TArray<GridPosition> ULrid::GetPath(GridPosition TargetPos)
{
	TArray<GridPosition> *ret = PathMap.Find(TargetPos);
	if (ret == nullptr)
		return TArray<GridPosition>();

	return *ret;
}

TArray<GridPosition> const ULrid::GetEndpoints() const
{
	TArray<GridPosition> keys;
	PathMap.GetKeys(keys);

	const TArray<GridPosition> ckeys = keys;
	
	return ckeys;
}