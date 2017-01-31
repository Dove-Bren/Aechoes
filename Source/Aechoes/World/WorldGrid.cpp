// Fill out your copyright notice in the Description page of Project Settings.

#include "Aechoes.h"
#include "WorldGrid.h"

GridPosition * AWorldGrid::translate(float x, float y)
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
    return 0.0f;
}

TWeakObjectPtr<ALivingCharacter> AWorldGrid::get(float x, float y)
{
    return TWeakObjectPtr<ALivingCharacter>();
}

bool AWorldGrid::isEmpty(float x, float y)
{
    return false;
}

bool AWorldGrid::place(float x, float y)
{
    return false;
}

bool AWorldGrid::clear(float x, float y)
{
    return false;
}
