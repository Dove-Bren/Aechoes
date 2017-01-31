// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "WorldGrid.h"

GridPosition AWorldGrid::translate(float x, float y)
{
    return GridPosition::from(x, y, this->scale);
}

AWorldGrid::AWorldGrid()
{
    this->scale = AWorldGrid::DEFAULT_SCALE;
    this->map = TMap<GridPosition, TWeakObjectPtr<ALivingCharacter>>();
}

float AWorldGrid::getScale()
{
    return scale;
}

ALivingCharacter *AWorldGrid::get(float x, float y)
{
    return (*map.Find(translate(x, y))).Get(true);
}

bool AWorldGrid::isEmpty(float x, float y)
{
    return map.Find(translate(x, y)) == nullptr;
}

bool AWorldGrid::place(float x, float y, ALivingCharacter *input)
{
    TWeakObjectPtr<ALivingCharacter> ret = *map.Find(translate(x, y));
    map.Add(translate(x, y), TWeakObjectPtr<ALivingCharacter>(input));

    return (ret) != nullptr;
}

bool AWorldGrid::clear(float x, float y)
{
    TWeakObjectPtr<ALivingCharacter> ret = *map.Find(translate(x, y));
    map.Remove(translate(x, y));

    return (ret) != nullptr;
}
