// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "AI/Navigation/NavigationSystem.h"
#include "WorldGrid.h"

GridPosition UWorldGrid::translate(float x, float y)
{
    return GridPosition::from(x, y, this->scale);
}

FVector UWorldGrid::snapTo(FVector const in, bool middle)
{
    FVector out = GridPosition::alignToGrid(in, this->scale);

    if (middle) {
        out.X += (scale / 2);
        out.Y += (scale / 2);
    }


    return out;
}

UWorldGrid::UWorldGrid()
{
    this->scale = UWorldGrid::DEFAULT_SCALE;
    this->map = TMap<GridPosition, TWeakObjectPtr<ALivingCharacter>>();
}

float UWorldGrid::getScale()
{
    return scale;
}

ALivingCharacter *UWorldGrid::get(float x, float y)
{
	GridPosition pos = translate(x, y);
	UE_LOG(LogTemp, Warning, TEXT("GridPos: [%d, %d]"), pos.x, pos.y);
	TWeakObjectPtr<ALivingCharacter> *ret = map.Find(pos);
	if (ret != nullptr && (*ret).IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Valid!"));
		return (*ret).Get(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("invalid!"));
	return nullptr;
}

bool UWorldGrid::isEmpty(float x, float y)
{
    return map.Find(translate(x, y)) == nullptr;
}

bool UWorldGrid::place(float x, float y, ALivingCharacter *input)
{
    TWeakObjectPtr<ALivingCharacter> *ret = map.Find(translate(x, y));
    map.Add(translate(x, y), TWeakObjectPtr<ALivingCharacter>(input));

	UE_LOG(LogTemp, Warning, TEXT("Placing object at %f, %f"), x, y);

    return (ret != nullptr && (*ret).IsValid());
}

bool UWorldGrid::clear(float x, float y)
{
	return map.Remove(translate(x, y)) > 0;
}

void UWorldGrid::clearAll()
{
    map.Empty();
}

FVector UWorldGrid::ToWorldPos(GridPosition GridPos) {
	return ToWorldPos(GridPos, false);
}

FVector UWorldGrid::ToWorldPos(GridPosition GridPos, bool middle)
{
	return ToWorldPos(GridPos, middle, false);
}

FVector UWorldGrid::ToWorldPos(GridPosition GridPos, bool middle, bool ToNav)
{
	FVector ret(GridPos.x * scale, GridPos.y * scale, 0);

	if (middle) {
		ret.X += (scale / 2.0f);
		ret.Y += (scale / 2.0f);
	}

	if (ToNav) {
		FVector in = ret;
		in = UNavigationSystem::ProjectPointToNavigation(
			GetWorld(), in, nullptr, 0, FVector(0.0f, 0.0f, 1000.0f));
		ret.Z = in.Z;
	}
	
	return ret;
}

GridPosition UWorldGrid::ToGridPos(FVector WorldPos)
{
	return translate(WorldPos.X, WorldPos.Y);
}

int32 UWorldGrid::GetGridDistance(FVector Pos1, FVector Pos2)
{
	GridPosition p1 = translate(Pos1.X, Pos1.Y),
		p2 = translate(Pos2.X, Pos2.Y);
	int32 dist = FMath::Abs<int32>(p1.x - p2.x);
	dist += FMath::Abs<int32>(p1.y - p2.y);
	return dist;
}