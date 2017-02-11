// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
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
    TWeakObjectPtr<ALivingCharacter> ret = *map.Find(translate(x, y));
    map.Remove(translate(x, y));

    return (ret) != nullptr;
}

void UWorldGrid::clearAll()
{
    map.Empty();
}

FVector UWorldGrid::ToWorldPos(GridPosition GridPos)
{
	return FVector(GridPos.x * scale, GridPos.y * scale, 0);
}

GridPosition UWorldGrid::ToGridPos(FVector WorldPos)
{
	return translate(WorldPos.X, WorldPos.Y);
}