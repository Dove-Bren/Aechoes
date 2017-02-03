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
    return (*map.Find(translate(x, y))).Get(true);
}

bool UWorldGrid::isEmpty(float x, float y)
{
    return map.Find(translate(x, y)) == nullptr;
}

bool UWorldGrid::place(float x, float y, ALivingCharacter *input)
{
    TWeakObjectPtr<ALivingCharacter> ret = *map.Find(translate(x, y));
    map.Add(translate(x, y), TWeakObjectPtr<ALivingCharacter>(input));

    return (ret) != nullptr;
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
